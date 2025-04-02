#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    int currentState;
    char symbol;
    int nextState;
} Transition;

int main()
{
    int numSymbols, numStates, numAcceptingStates, numTransitions;
    int initialState;

    printf("Define Finite Automata\n");

    // Input number of symbols
    printf("Number of input symbols: ");
    scanf("%d", &numSymbols);
    char *symbols = (char *)malloc(numSymbols * sizeof(char));
    printf("Input symbols (space-separated): ");
    for (int i = 0; i < numSymbols; i++)
    {
        scanf(" %c", &symbols[i]);
    }

    // Input number of states
    printf("Enter number of states: ");
    scanf("%d", &numStates);
    int *states = (int *)malloc(numStates * sizeof(int));
    for (int i = 0; i < numStates; i++)
    {
        states[i] = i + 1;
    }

    // Initial state
    printf("Initial state: ");
    scanf("%d", &initialState);

    // Accepting states
    printf("Number of accepting states: ");
    scanf("%d", &numAcceptingStates);
    int *acceptingStates = (int *)malloc(numAcceptingStates * sizeof(int));
    printf("Accepting states (space-separated): ");
    for (int i = 0; i < numAcceptingStates; i++)
    {
        scanf("%d", &acceptingStates[i]);
    }

    // Transitions
    numTransitions = numStates * numSymbols;
    Transition *transitions = (Transition *)malloc(numTransitions * sizeof(Transition));
    printf("Transition table: (Format: <state> <symbol> <next_state>)\n");
    for (int i = 0; i < numTransitions; i++)
    {
        scanf("%d %c %d", &transitions[i].currentState, &transitions[i].symbol, &transitions[i].nextState);
    }

    // Loop to process multiple input strings
    char inputString[100];
    char choice;
    do
    {
        // Input string
        printf("Input string to validate: ");
        scanf("%s", inputString);

        // Validate input string
        int currentState = initialState;
        bool isValid = true;

        for (int i = 0; i < strlen(inputString); i++)
        {
            char currentSymbol = inputString[i];
            bool transitionFound = false;

            for (int j = 0; j < numTransitions; j++)
            {
                if (transitions[j].currentState == currentState && transitions[j].symbol == currentSymbol)
                {
                    currentState = transitions[j].nextState;
                    transitionFound = true;
                    break;
                }
            }

            if (!transitionFound)
            {
                isValid = false;
                break;
            }
        }

        if (isValid)
        {
            // Check if current state is accepting
            bool isAccepting = false;
            for (int i = 0; i < numAcceptingStates; i++)
            {
                if (currentState == acceptingStates[i])
                {
                    isAccepting = true;
                    break;
                }
            }

            if (isAccepting)
            {
                printf("Valid String\n");
            }
            else
            {
                printf("Invalid String\n");
            }
        }
        else
        {
            printf("Invalid String\n");
        }

        // Ask user if they want to validate another string
        printf("Do you want to validate another string? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    printf("Exiting program.\n");

    // Free allocated memory
    free(symbols);
    free(states);
    free(acceptingStates);
    free(transitions);

    return 0;
}
