#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STATES 100
#define MAX_SYMBOLS 100

typedef struct
{
    int currentState;
    char symbol;
    int nextState;
} Transition;

int main()
{
    int numSymbols, numStates, numAcceptingStates, numTransitions;
    char symbols[MAX_SYMBOLS];
    int states[MAX_STATES];
    int acceptingStates[MAX_STATES];
    Transition transitions[MAX_STATES * MAX_SYMBOLS];
    int initialState;

    printf("Define Finite Automata\n");

    // Input symbols
    printf("Number of input symbols: ");
    scanf("%d", &numSymbols);
    printf("Input symbols (space-separated): ");
    for (int i = 0; i < numSymbols; i++)
    {
        scanf(" %c", &symbols[i]);
    }

    // States
    printf("Enter number of states: ");
    scanf("%d", &numStates);
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
    printf("Accepting states (space-separated): ");
    for (int i = 0; i < numAcceptingStates; i++)
    {
        scanf("%d", &acceptingStates[i]);
    }

    // Transitions
    numTransitions = numStates * numSymbols;
    printf("Transition table: (Format: <state> <symbol> <next_state>)\n");
    for (int i = 0; i < numTransitions; i++)
    {
        scanf("%d %c %d", &transitions[i].currentState, &transitions[i].symbol, &transitions[i].nextState);
    }

    // Process multiple input strings
    char inputString[100];
    char choice;
    do
    {
        // Input string
        printf("Input string to validate: ");
        scanf("%s", &inputString);

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
        scanf(" %c", choice);
    } while (choice == 'y' || choice == 'Y');

    printf("Exiting program.\n");
    return 0;
}
