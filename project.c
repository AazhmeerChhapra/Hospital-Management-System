
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//-------------------------------------------------------------------
// capacity of beds in hospital
#define MAX_BED 10
//-------------------------------------------------------------------

//-------------------------------------------------------------------

// Linked list structure
struct Node
{
    int age;           // stores the age of patient
    char name[20];     // stores the name of patienr
    char disease[20];  // stores the name of disease
    int bed_no;        // number of beds
    struct Node *next; // our next pointer to point to next node
};
//-------------------------------------------------------------------

//-------------------------------------------------------------------

// ours three heads that will point toward the start of each linked list
struct Node *head_history = NULL;   // head for history linked list
struct Node *head_available = NULL; // head for linked list containg the available beds
struct Node *head_occupied = NULL;  // head for linked list containing occupied beds
int counter_available = 0;
int count = 1;
int bed_occupied; // takes bed no in which patient will be admitted
int age;
int k = 0;
char name[20];
char disease[20];
//-------------------------------------------------------------------
// This function will be used to sort linked list of available beds
struct Node *sortList(struct Node *head)
{
    // Node current will point to head
    struct Node *current = head, *index = NULL;
    int temp;

    if (head == NULL)
    {
        return NULL;
    }
    else
    {
        while (current != NULL)
        {
            // Node index will point to node next to current
            index = current->next;

            while (index != NULL)
            {
                // If current node's bed_no is greater than index's node bed_no, swap the bed_no between them
                if (current->bed_no > index->bed_no)
                {
                    temp = current->bed_no;
                    current->bed_no = index->bed_no;
                    index->bed_no = temp;
                }
                index = index->next;
            }
            current = current->next;
        }
    }
    return head;
}

//-------------------------------------------------------------------
// this function will insert no of beds availabel for patients in linked list of
// available beds
struct Node *insertionofBeds(struct Node *head, int bed_no) // insertion from end
{
    if (head == NULL)
    {
        head = (struct Node *)malloc(sizeof(struct Node));
        head->bed_no = bed_no;
        head->next = NULL;
    }
    else
    {
        struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
        ptr->bed_no = bed_no;
        struct Node *p = head;
        while (p->next != NULL)
        {
            p = p->next;
        }

        p->next = ptr;
        ptr->next = NULL;
    }

    return head;
}
// This function will add those beds again in available beds linked list from which patients are discharged and beds are now free.
struct Node *addingEmptyBeds(struct Node *head, int bed_no)
{
    struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
    struct Node *p = head;
    ptr->bed_no = bed_no;
    int i = 0;
    while (i != bed_no - 1)
    {
        p = p->next;
        i++;
    }

    ptr->next = p->next;
    p->next = ptr;
    head = sortList(head);
    printf("%d bed is added back to available beds\n", bed_no);
    return head;
}
//-------------------------------------------------------------------
// Call to inserttionofBeds function to actually insert the bed number in linked list
void available_beds()
{

    for (int i = 1; i <= MAX_BED; i++)
    {
        head_available = insertionofBeds(head_available, i);
        counter_available++;
    }
}
//---------------------------------------------------------------------
struct Node *occupyingofBeds(struct Node *head, int bed_no, char name[], char disease[], int age) // insertion from end
{
    if (head == NULL)
    {
        head = (struct Node *)malloc(sizeof(struct Node));
        head->bed_no = bed_no;
        strcpy(head->name, name);
        strcpy(head->disease, disease);
        head->age = age;
        head->next = NULL;
    }
    else
    {
        struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
        ptr->bed_no = bed_no;
        strcpy(ptr->name, name);
        strcpy(ptr->disease, disease);
        ptr->age = age;
        struct Node *p = head;
        while (p->next != NULL)
        {
            p = p->next;
        }

        p->next = ptr;
        ptr->next = NULL;
    }

    return head;
}
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// This function will be used when all beds are filled once and now random beds are discharged we can give those beds to patients.
struct Node *occupyAtAnyBed(struct Node *head, int bed_no, char name[], char disease[], int age)
{
    if (head == NULL)
    {
        head = (struct Node *)malloc(sizeof(struct Node));
        head->bed_no = bed_no;
        strcpy(head->name, name);
        strcpy(head->disease, disease);
        head->age = age;
        head->next = NULL;
        return head;
    }
    else
    {
        struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
        struct Node *p = head;
        ptr->bed_no = bed_no;
        ptr->bed_no++; // added new
        strcpy(ptr->name, name);
        strcpy(ptr->disease, disease);
        ptr->age = age;
        int i = 0;
        while (i != bed_no - 1)
        {
            p = p->next;
            i++;
        }

        ptr->next = p->next;
        p->next = ptr;
        return head;
    }
}

//-------------------------------------------------------------------
// This function will display the available beds
void displayAvailableBeds()
{
    struct Node *n = head_available;
    printf("Beds available:\n");
    while (n->next != NULL)
    {
        printf("%d ", n->bed_no);
        n = n->next;
    }
    printf("%d ", n->bed_no);
    printf("\n");
}
// This function will display occupied beds linked list
void displayOccupiedBeds()
{
    struct Node *n = head_occupied;
    head_occupied = sortList(head_occupied);
    printf("Occupied beds are: \n");

    while (n != NULL)
    {
        printf("\nbed no: %d \n", n->bed_no);

        printf("patient name:");

        puts(n->name);
        printf("patient disease:");

        puts(n->disease);
        printf("age is %d \n", n->age);

        n = n->next;
        //  n->bed_no++;
    }

    // printf("\nbed no: %d \n", n->bed_no);
    // printf("patient name:");
    // puts(n->name);
    // printf("patient disease:");
    // puts(n->disease);
    // printf("age is :%d ", n->age);
    // printf("\n");
}
// This function will be used to display history of all the patients.
void displayHistory()
{
    struct Node *n = head_history;
    printf("Details of patients are: \n");
    while (n->next != NULL)
    {
        printf("\nbed no: %d \n", n->bed_no);
        printf("patient name:");

        puts(n->name);
        printf("patient disease:");

        puts(n->disease);
        printf("age is %d ", n->age);

        n = n->next;
    }
    printf("\nbed no: %d \n", n->bed_no);
    printf("patient name:");
    puts(n->name);
    printf("patient disease:");
    puts(n->disease);
    printf("age is :%d ", n->age);
    printf("\n");
}
//---------------------------------------------------------------
struct Node *deleteStartAvailableBed(struct Node *head) // this function will delete available beds as they are occupied from start in a sequence
{
    struct Node *ptr = head;
    head = head->next;
    free(ptr);
    return head;
}
//---------------------------------------------------------------
// this functioin will delete the bed number from available beds after
// that bed is occupied by new patirnt

struct Node *deleteAnyBed(struct Node *head, int bed_no)
{
    struct Node *p = head;
    struct Node *q = head->next;
    if (head == NULL)
    {
        printf("This bed is already empty");
        return NULL;
    }
    else if (head->bed_no == bed_no) // added new
    {
        head = head->next;
        free(p);
    }

    else
    {
        for (int i = 1; i < bed_no - 1; i++)
        {
            p = p->next;
            q = q->next;
        }

        p->next = q->next;
        free(q);
    }

    return head;
}
//---------------------------------------------------------------

//---------------------------------------------------------------
void insertAtDischarge(struct Node *head) // Add patients on those beds which are discharged
{
    int flag = 0;
    struct Node *compare = head;
    char name[40];
    char disease[40];
    int age;
    int i = 1;
    int specific_bed;
    printf("Enter Bed Number on which you want to add a patient : ");
    scanf("%d", &specific_bed);

    while (compare != NULL)
    {
        if (compare->bed_no == specific_bed)
        {
            flag = 1;
            printf("patient name:");
            getchar();
            gets(name);
            printf("patient disease:");
            gets(disease);
            printf("Enter age:");
            scanf("%d", &age);
            head_occupied = occupyAtAnyBed(head_occupied, i, name, disease, age);
            printf("ok\n");
            head_available = deleteAnyBed(head_available, specific_bed);
        }
        compare = compare->next;
        i++;
    }

    if (flag == 0)
    {
        printf("bed Number not found in list\n");
    }
}
void addPatientsInSequence() // adding patients in sequence
{
    if (count <= MAX_BED)
    {
        printf("patient name:");
        getchar();
        gets(name);
        printf("patient disease:");
        gets(disease);
        printf("Enter age:");
        scanf("%d", &age);
        head_occupied = occupyingofBeds(head_occupied, count, name, disease, age);
        head_history = occupyingofBeds(head_history, count, name, disease, age);
        printf("Bed no %d is now occupied: ", count);
        count++;
        head_available = deleteStartAvailableBed(head_available);

        printf("\n");
    }
    else
    {
        printf("BEDS are full");
    }
    displayOccupiedBeds();
}
void dischargePatient() // discharging patients on pressing 3
{
    int discharge_bed, flag = 0;
    printf("Enter bed which is being empty: ");
    scanf("%d", &discharge_bed);
    struct Node *ptr = head_occupied;
    if (head_occupied == NULL)
    {
        printf("Empty list \n");
        
       
    }

    while (ptr != NULL)
    {
        if (ptr->bed_no == discharge_bed)
        {
            head_occupied = deleteAnyBed(head_occupied, discharge_bed);
            head_available = addingEmptyBeds(head_available, discharge_bed);
            flag = 1;
        }
        ptr = ptr->next;
    }
    if (flag == 0)
    {
        printf("Bed is already free\n");
    }
}
int main()
{

    int option;

    available_beds(); // This will stores the available bed number in linked list

    while (option != -1)
    {
        printf("1-display available beds\n2-Admit a patient on available beds(in sequence)\n3-discharge a patient if beds are full or a patient is healed\n4-Add patients on available beds\n5-display Occupied beds\n6-display history\n-1 to exit\nEnter Option:");

        scanf("%d", &option);
        switch (option)
        {
        case 1:
        {
            displayAvailableBeds(); // This will print the available beds number linked list
            break;
        }

        case 2:
        {
            addPatientsInSequence();
            break;
        }
        case 3:
        {
            dischargePatient();
            break;
        }
        case 4: // This case is used to add patients on available beds after filling
        {
            if (count > 0)
            {
                insertAtDischarge(head_available);
            }
            break;
        }
        case 5:
            displayOccupiedBeds();
            break;

        case 6:
            displayHistory();
            break;

        default:
            break;
        }
    }

    //-------------------------------------------------------------------
    // prompting

    system("pause");
    return 0;
}