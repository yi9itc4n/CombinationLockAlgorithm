#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX 100

typedef struct node
{
    int data;
    struct node *next;
} Node;
void
printLinkedList (Node * List)
{
    printf ("Linked list: ");
    printf ("%d ", List->data);
    Node *curr = List->next;
    while (curr != NULL)
    {
        printf ("%d ", curr->data);
        curr = curr->next;
    }
    printf ("\n");
}

Node *
createLinkedList (int numElements, int maxVal, int *usedVals)
{
    int i;
    Node *head = NULL;
    Node *tail = NULL;



    for (i = 0; i < numElements; i++)
    {

        int val = (rand () % maxVal) + 1;
        usedVals[val]++;
        if (usedVals[val] == 1)
        {

            Node *newNode = (Node *) malloc (sizeof (Node));
            newNode->data = val;
            newNode->next = NULL;


            if (head == NULL)
            {
                head = newNode;
                tail = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
            }
        }
        else
            numElements++;
    }

    return head;
}

Node *
arayaEkle (Node * List, int commonVal, int index)
{
    int i;
    Node *curr = List;
    Node *temp = malloc (sizeof (Node));
    if (index != 0)
    {
        for (i = 1; i < (index); ++i)
        {
            curr = curr->next;
        }
        temp->next = curr->next;
        curr->next = temp;
        temp->data = commonVal;
        return List;
    }
    else
    {
        temp->next = curr;
        temp->data = commonVal;
        return temp;
    }

}

void
kisaYol (int index0, int index, int M, Node * List)
{
    int hareket, i;
    char yon[4];
    Node *curr = malloc (sizeof (Node));
    curr = List;
    if (index0 > index)
    {
        if (index0 - index > index + M - index0)
        {
            hareket = index + M - index0;
            strcpy (yon, "sol");
        }
        else
        {
            hareket = index0 - index;
            strcpy (yon, "sag");
        }
    }

    else
    {
        if (index - index0 > index0 + M - index)
        {
            hareket = index0 + M - index;
            strcpy (yon, "sag");
        }
        else
        {
            hareket = index - index0;
            strcpy (yon, "sol");
        }
    }

    printf ("%d birim %sa kaydirilmali yeni hali:\n", hareket, yon);
    if (strcmp (yon, "sag"))
    {
        for (i = 0; i < hareket; ++i)
        {
            curr = curr->next;
        }
        while (curr != NULL)
        {
            printf ("%d ", curr->data);
            curr = curr->next;
        }
        for (i = 0; i < hareket; ++i)
        {
            printf ("%d ", List->data);
            List = List->next;
        }
    }
    else
    {
        for (i = 0; i < M - hareket; ++i)
        {
            curr = curr->next;
        }
        while (curr != NULL)
        {
            printf ("%d ", curr->data);
            curr = curr->next;
        }
        for (i = 0; i < M - hareket; ++i)
        {
            printf ("%d ", List->data);
            List = List->next;
        }
    }

}

int
main ()
{
    int M, N, randomIndex[MAX] = { 0 }, i, commonVal, usedVals[MAX] =
            {
                    0}, kontrol;
    while (kontrol != 1)
    {
        kontrol = 1;
        printf ("Eleman sayısını giriniz: ");
        scanf ("%d", &M);
        printf ("Maximum değeri giriniz: ");
        scanf ("%d", &N);
        if (N < 3 * M - 2)
        {
            kontrol = 0;
            printf ("\n\nHatali giris yapildi. Tekrar deneyin\n\n");
        }
    }
    srand (time (NULL));
    Node *temp = malloc (sizeof (Node));
    Node *List1 = createLinkedList (M, N, usedVals);


    //digerlerinde de olacak elemani rastgele belirleme
    Node *curr = List1;
    randomIndex[0] = rand () % M;
    for (i = 0; i < randomIndex[0]; ++i)
    {
        curr = curr->next;
    }
    commonVal = curr->data;
    //diger listelerde gelecegi indexi rastgele belirleme ve listeleri olusturma
    randomIndex[1] = rand () % M;
    if (randomIndex[1] == randomIndex[0])
    {
        while (randomIndex[1] == randomIndex[0])
            randomIndex[1] = rand () % M;
    }
    Node *List2 = createLinkedList (M - 1, N, usedVals);
    List2 = arayaEkle (List2, commonVal, randomIndex[1]);

    randomIndex[2] = rand () % M;
    if (randomIndex[2] == randomIndex[0] || randomIndex[2] == randomIndex[1])
    {
        while (randomIndex[2] == randomIndex[0]
               || randomIndex[2] == randomIndex[1])
            randomIndex[2] = rand () % M;
    }
    Node *List3 = createLinkedList (M - 1, N, usedVals);
    List3 = arayaEkle (List3, commonVal, randomIndex[2]);
    printf ("\nOrtak değer: %d ve Indexler: %d,%d,%d\n\n", commonVal,
            randomIndex[0], randomIndex[1], randomIndex[2]);

    printLinkedList (List1);
    printLinkedList (List2);
    printLinkedList (List3);
    printf ("\n\n2. liste ");
    kisaYol (randomIndex[0], randomIndex[1], M, List2);
    printf ("\n\n3. liste ");
    kisaYol (randomIndex[0], randomIndex[2], M, List3);
    return 0;
}
