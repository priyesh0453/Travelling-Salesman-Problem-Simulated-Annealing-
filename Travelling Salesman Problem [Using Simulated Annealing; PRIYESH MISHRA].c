#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 10    //Number of cities. With just changing value of N, nothing else needs to be modified.

void printIndices(int indices[N][2])    //Prints the order of points with their indices.
{
    printf("\n");
    int i = 0;
    
    for(; i < N; i++)
    {
        printf("Point %d: ", (i+1));
        printf("(%d, %d)", indices[i][0], indices[i][1]);
        printf("\n");
    }
    
    printf("\n");
}

void shuffleArray(int indices[N][2])    //Shuffles the order of all points randomly.
{
    int i = N - 1, j = 0, temp, k;
    
    srand(time(NULL));
    
    for(; i > 0; i--)
    {
        j = rand() % (i + 1);
        
        for(k = 0; k < 2; k++)
        {
            temp = indices[i][k];   //Swapping of points/indices via a temporary variable.
            indices[i][k] = indices[j][k];
            indices[j][k] = temp;
        }
    }
}

void shuffle2Points(int indices[N][2])  //Shuffles randomly a point of the matrix including order of all points with it's consecutive one.
{
    int randomPos = rand() % N, temp, i = 0;
    
    for (; i < 2; i++)
    {
        temp = indices[randomPos][i];
        indices[randomPos][i] = indices[(randomPos + 1) % N][i];
        indices[(randomPos + 1) % N][i] = temp;
    }
}

float totalDistance(int indices[N][2])  //To calculate total distance of the loop formed by the points in the current matrix.
{
    int i = 0, j = N - 1;
    float totalDist = 0.0f;
    
    for(; i < j; i++)
    {
        totalDist += sqrt(pow(indices[i+1][0] - indices[i][0], 2) + pow(indices[i+1][1] - indices[i][1], 2));
    }
    return totalDist + sqrt(pow(indices[N-1][0] - indices[0][0], 2) + pow(indices[N-1][1] - indices[0][1], 2));
}

int main()
{
    int indices[N][2], i = 0, j, check2 = (100 * N);
    float dist_i = 0.0f, factor = 0.9f, probability = 0.0f, randomProb, dist_trial, T = (N * 20);
    
    printf("Enter the indices (taken in 2D matrix form or order (N*2)) (for our case, N = 10, therefore 20 values):\n");
    
    for(; i < N; i++)
    {
        for(j = 0; j < 2; j++)
        {
            scanf("%d", &indices[i][j]);    //accept the indices of 10 points/cities from the user.
        }
    }
    
    printIndices(indices);  //print the indices entered by the user.
    
    i = 0, dist_i = totalDistance(indices);
    
    while(T > 0.1f)     //Terminating condition for loop wherein T (tempterature, in this case in units of distance) falls below 0.1
    {
        shuffleArray(indices);      //Shuffle the order of all points on the change of the value of tempterature (T).
        dist_trial = totalDistance(indices);    //Trial's distance or cost
        
        for(; i < check2; i++)    //For each tempterature (T), 1000 confirgurations are compared.
        {
            shuffle2Points(indices);    //Shuffle any random points among themselves.
            dist_trial = totalDistance(indices);
            
            if(dist_trial <= dist_i)     //If the latest trial's cost is less than the old confirguration's cost; Accept the new value.
            {
                dist_i = dist_trial;
            }
            else
            {
                randomProb = (float) rand() / ((float) RAND_MAX);   //random number in [0,1] to be compared with annealing's probability calculated below.
                probability = exp((-1 * (dist_trial / T))) / exp((-1 * (dist_i / T)));
                
                if(randomProb < probability)    // if r (random number) < w (probability based on annealing's algo), accept the new value.
                {
                    dist_i = dist_trial;
                }
            }
        }
        
        i = 0;  //Reset the value for new value of T.
        T = T * factor;     //Stepping down the T (factor is taken as 0.9); Can be modified by the user.
    }
    
    printf("The shortest distance for the given indices (by the user) is %f (units).", dist_i);  //Prints the shortest distance for the TSP for the given indices by the user.
    
    return 0;
}