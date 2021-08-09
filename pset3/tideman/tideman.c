#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void mergesort(pair array[], int left, int right);
void merge(pair array[], int left, int mid, int right);
int strength(pair p);
bool valid_graph(int winner, int loser);


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        //Check that the candidate name is valid
        if (strcmp(candidates[i], name) == 0)
        {
            //Add that candidate's element number in candidates[] to ranks[] in the next slot (==rank)
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //Iterate over each element in ranks[]
    for (int i = 0; i < candidate_count; i++)
    {
        //Iterate over rest of elements to the right of ranks[i] to determine preferences
        for (int j = i + 1; j < candidate_count; j++)
        {
            //Increment elements to show voter preference for candidate ranks[i] over candidate ranks[j]
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            //Check to see if Candidate A beats Candidate B
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    mergesort(pairs, 0, pair_count - 1);
    return;
}

//Sort the pairs array
void mergesort(pair array[], int left, int right)
{
    if (left < right)
    {
        //Find middle of (sub)array to split
        int mid = (left + right) / 2;
        //Sort the left half
        mergesort(array, left, mid);
        //Sort the right half
        mergesort(array, mid + 1, right);

        //Merge the two halves
        merge(array, left, mid, right);
    }
}

//Merge the sorted pairs sub-arraays
void merge(pair array[], int left, int mid, int right)
{
    int i = left; //Start of the left sub-array
    int j = mid + 1; //Start of the right sub-array
    int k = left; //Pointer for temp[] array
    pair temp[right];

    //Sort each sub-array into the temp array based on strength of each pair
    while (i <= mid && j <= right)
    {
        //If the next element in the left array is stronger, it goes next
        if (strength(array[i]) >= strength(array[j]))
        {
            temp[k] = array[i];
            i++;
        }
        //If the next element in the right array is stronger, it goes next
        else
        {
            temp[k] = array[j];
            j++;
        }
        k++;
    }

    //Put any remaining elements into temp
    while (i <= mid)
    {
        temp[k] = array[i];
        i++;
        k++;
    }
    while (j <= right)
    {
        temp[k] = array[i];
        j++;
        k++;
    }

    //Copy temp[] elements back into original array[]
    for (i = left, k = 0; i <= right; i++, k++)
    {
        array[i] = temp[k];
    }
}

//Get the strength of a pair
int strength(pair p)
{
    int w = p.winner;
    int l = p.loser;
    //By how much is the winner preferred over the loser?
    int strength = preferences[w][l] - preferences[l][w];
    return strength;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        //Get the winner and loser of the next pair in pairs[]
        int w = pairs[i].winner;
        int l = pairs[i].loser;

        //Add pair to locked[] if it does not create a loop
        if (valid_graph(w, l))
        {
            locked[w][l] = true;
        }
    }
    return;
}

//Check that the edge graph does not create a loop (sourceless graph)
bool valid_graph(int winner, int loser)
{
    for (int j = 0; j < candidate_count; j++)
    {
        //If the loser has beaten someone else...
        if (locked[loser][j])
        {
            //...and that next loser beat the current winner, the graph is invalid
            if (winner == j)
            {
                return false;
            }
            //...see if that next loser beat the current winner
            else if (!valid_graph(winner, j))
            {
                return false;
            }
        }
    }
    //Adding the edge does NOT create a looping graph
    return true;
}

// Print the winner of the election
void print_winner(void)
{
    int falses = 0;
    //Iterate over each column
    for (int j = 0; j < candidate_count; j++)
    {
        //Iterate down each row of the column
        for (int i = 0; i < candidate_count; i++)
        {
            //If encounter a true, skip to next column
            if (locked[i][j])
            {
                falses = 0;
                break;
            }
            //Keep track of how many false values there are in the column
            else
            {
                falses++;
            }
        }
        //If a candidate's column is all false, they are the source!
        if (falses == candidate_count)
        {
            printf("%s\n", candidates[j]);
        }
    }
    return;
}