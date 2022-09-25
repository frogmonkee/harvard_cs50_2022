// https://cs50.harvard.edu/x/2022/psets/3/tideman/
// https://gist.github.com/nicknapoli82/6c5a1706489e70342e9a0a635ae738c9

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
bool cycle(int pair_winner, int loser);

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
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Initialize one dimension of preferences array
    for (int i = 0; i < candidate_count; i++)
    {
        // Initialize second dimension of preferences array
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Increment number of votes who prefere candidate i over j
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Initialize one dimension of preferences array at 0
    for (int i = 0; i < candidate_count; i++)
    {
        // Initialize second dimension as i + 1 as to not compare one index against itself
        // I drew out a matrix to identify pairs. This was the algorithm that made sense
        for (int j = i + 1; j < candidate_count; j++)
        {
            // If value as position (i, j) is greater than (j, i) then valid pair and store winner/loser
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            // If value as position (i, j) is less than (j, i) then valid pair and store winner/loser
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int strength_i;
    int strength_j;
    // Initialize index value for first dimension of preferences[i][j]
    for (int i = 0; i < pair_count; i++)
    {
        // Calculate edge strength for each pair starting at index i
        strength_i = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
        // Initialize index value for second dimension of preferences[i][j]
        for (int j = i + 1; j < pair_count; j++)
        {
            // Calculate edge strength for each pair starting at the element right after index i
            strength_j = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            // If strength of elements further along the array is larger then the strength at index i, then swap elements
            if (strength_j > strength_i)
            {
                // Swap elements i and j for pair array
                pair temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
                // Set strength of the freshly swapped index i
                strength_i = strength_j;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Initialize index for each element of pairs[]
    for (int i = 0; i < pair_count; i++)
    {
        // Call cycle function
        if (!cycle(pairs[i].winner, pairs[i].loser))
        {
            // If cycle returns false, locked in pair
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

bool cycle(int pair_winner, int loser)
{
    // Initialize i to search through each row
    for (int i = 0; i < candidate_count; i++)
    {
        // Pass in loser from pairs[i]
        // If locked position exists & original winner lost, then cycle exists
        if (locked[loser][i] == true && pair_winner == i)
        {
            return true;
        }
        // If locked position exists, but original winner is not the loser, go one layer deeper and
        else if (locked[loser][i] == true && pair_winner != i)
        {
            if (cycle(pair_winner, i))
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // Initialize rows of locked array
    for (int i = 0; i < candidate_count; i++)
    {
        // Sum refers to the total number of locked pairs within a column
        int sum = 0;
        // Initialize column of locked array
        for (int j = 0; j < candidate_count; j++)
        {
            // Sum all elements of a single column in locked[][]
            // Note that locked[][] inverts i and j. locked[i][j] would sum all elements of the row
            sum += locked[j][i];
        }
        // Sum == 0 represents no locked pairs for a candidate's column, meaning there are no edges pointing to it
        if (sum == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
