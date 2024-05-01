#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Activity
{
    char Id[30];
    float duration;
    int Est;
    int Lst;
    int Eet;
    int Let;
    int Cost;
    struct Activity *Successors[100];
    struct Activity *Predecessors[100];
}activity;

int numActivities,critical;
activity *List[100],*check,*check2, *activityInstance;

void GetActivities();
void WalkListAhead();
void WalkListAback();
void CriticalPath();

void CheckActivity(activity *act, int i)
{
    for(int j = 0; j < i; j++)
    {
        if(strcmp(List[j]->Id, act->Id) == 0)
        {
            check = List[j];
            return;
        }
    }
    check = NULL;
}


int GetIndex(activity *act, int i)
{
    for(int j = 0; j < i; j++)
    {
        if(strcmp(List[j]->Id, act->Id) == 0)
        {
            return j;
        }
    }
    return -1;
}

int SetSuccessors(activity *act)
{
    int i;
    for(i = 0; act->Successors[i] != NULL; i++);
    return i;
}

void printGraphviz() {
    FILE* file = fopen("graph.dot", "w");
    if (file != NULL) {
        fprintf(file, "digraph G {\n");
        for(int i = 0; i < numActivities; i++) {
            activity *act = List[i];
            if ((act->Eet - act->Let) == 0 && (act->Est - act->Lst) == 0) {
                fprintf(file, "    \"%s\" [label=\"ID: %s\\nDuration: %.2f\\nCost: %d\\nEst: %d\\nLet: %d\", fontcolor=red, fontsize=16];\n", act->Id, act->Id, act->duration, act->Cost, act->Est, act->Let);
            } else {
                fprintf(file, "    \"%s\" [label=\"ID: %s\\nDuration: %.2f\\nCost: %d\\nEst: %d\\nLet: %d\"];\n", act->Id, act->Id, act->duration, act->Cost, act->Est, act->Let);
            }
            for(int j = 0; act->Successors[j] != NULL; j++) {
                fprintf(file, "    \"%s\" -> \"%s\";\n", act->Id, act->Successors[j]->Id);
            }
        }
        fprintf(file, "}\n");
        fclose(file);
    } else {
        printf("Failed to open file.\n");
    }
}

void GetActivities()
{
    FILE *file = fopen("activities.csv", "r");
    if (file == NULL) {
        printf("Could not open file activities.csv\n");
        return;
    }

    fscanf(file, "%d", &numActivities);

    for(int i = 0; i < numActivities; i++)
    {
        activityInstance = (activity*)malloc(sizeof(activity));
        activityInstance->Predecessors[0]=NULL;
        activityInstance->Successors[0]=NULL;

        fscanf(file, "%29s", activityInstance->Id);
        fscanf(file, "%f", &activityInstance->duration);
        fscanf(file, "%d", &activityInstance->Cost);

        int np;
        fscanf(file, "%d", &np);
        List[i] = activityInstance;

        if(np != 0) {
            char id[30];
            for(int j = 0; j < np; j++)
            {
                fscanf(file, "%29s", id);
                activityInstance->Predecessors[j] = (activity*)malloc(sizeof(activity));
                activity *aux;
                aux =(activity*)malloc(sizeof(activity));
                int result;
                CheckActivity(id, i);
                if(check != NULL) {
                    activityInstance->Predecessors[j] = check;
                    result = GetIndex(check, i);
                    int k = SetSuccessors(List[result]);
                    List[result]->Successors[k] = activityInstance;
                } else {
                    printf("\n not matching try again.\n\n");
                    j--;
                }
            }
        } else {
            activityInstance->Predecessors[0]=NULL;
        }
    }

    fclose(file);
}

void WalkListAhead()
{
    for(int i = 0; i < numActivities; i++)
    {
        if(List[i]->Predecessors[0]==NULL) {
            List[i]->Est=0;
            List[i]->Eet=List[i]->duration;
        } else {
            int k=0;
            List[i]->Est=0;
            while (List[i]->Predecessors[k]!=NULL) {
                if(List[i]->Est < List[i]->Predecessors[k]->Eet)
                    List[i]->Est = List[i]->Predecessors[k]->Eet;
                k++;
            }
            List[i]->Eet = List[i]->Est + List[i]->duration;
        }
    }
}

void WalkListAback()
{
    int i;
    int max=List[0]->Eet;
    for(i=1;i<numActivities;i++)
    {
        if(List[i]->Eet>max)
            max=List[i]->Eet;
    }
    critical=max;
    int k=numActivities-1;
    for(int i=k; i>=0; i--)
    {
        if(List[i]->Successors[0]!=NULL) {
            int k=0;
            List[i]->Let=List[i]->Successors[0]->Lst;
            while (List[i]->Successors[k]!=NULL) {
                if(List[i]->Let > List[i]->Successors[k]->Lst)
                    List[i]->Let = List[i]->Successors[k]->Lst;
                k++;
            }
            List[i]->Lst = List[i]->Let-List[i]->duration;
        } else {
                List[i]->Let=max;
         List[i]->Lst=max-List[i]->duration;
      }
   }
}

void CriticalPath()
{
    for(int i=0; i<numActivities;i++)
    {
        printf("\n\tNode %d = %s", i, List[i]->Id);
        printf("\n\tduration = %.2f", List[i]->duration);
        printf("\n\tES = %d", List[i]->Est);
        printf("\n\tEF = %d", List[i]->Eet);
        printf("\n\tLS = %d", List[i]->Lst);
        printf("\n\tLF = %d", List[i]->Let);
        printf("\n\tCost = %d\n\n", List[i]->Cost);
    }
    printf("\n\tcritical activities: ");
    printf("\n");

    int total_cost;
    total_cost = 0;
    for(int i=0;i<numActivities;i++)
    {
        if((List[i]->Eet - List[i]->Let) == 0 && (List[i]->Est - List[i]->Lst)== 0)
            printf("\t%s\n", List[i]->Id);
            total_cost += List[i]->Cost;
    }
    printf("\n\n\tTotal duration: \t%d", critical);
    printf("\n\tTotal cost : \t%d", total_cost);
    printf("\n\n");
}

int main ()
{
    char Key;
    do {
        for(int i = 0; i < numActivities; i++) {
            List[i] = NULL;
        }
        GetActivities();
        WalkListAhead();
        WalkListAback();
        CriticalPath();
        printGraphviz();
        printf(" again? y\\n: ");
        scanf(" %c", &Key);
    } while(Key == 'y' || Key == 'Y');

    // Free the memory allocated for the activities
    for(int i = 0; i < numActivities; i++) {
        free(List[i]);
    }
}
