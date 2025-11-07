#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


struct sEmployee
{
    int ID;
    char Name[30];
    float Salary;
};

void gotoxy(int column, int line)
{
    COORD coord;
    coord.X=column;
    coord.Y=line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void textattr(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}

void MainMenu(int Option, char Menu[5][10])
{
    system("cls");
    for(int i=0; i<5; i++)
    {
        gotoxy(10, 10+i);
        if(Option==i)
            textattr(0x04);
        _cprintf("%s", Menu[i]);
        textattr(0x07);
    }
}

void SubMenu(int SubOption, int Option, char DisplaySubMenu[3][20])
{
    for(int j=0; j<3; j++)
                {
                    gotoxy(25, 12+j);
                    if(SubOption==j)
                        textattr(0x04);

                    _cprintf("%s", DisplaySubMenu[j]);
                    textattr(0x07);
                }
}


int getEmployeeCount()
{
    int size;
    printf("Please enter number of employees : ");
    scanf("%d", &size);
    return size;
}

void initializeEmployees(struct sEmployee *employees, int size)
{
    for(int i=0; i<size; i++)
    {
        (employees+i)->ID=-1; // -1 indicates an empty slot
    }
}

int findEmployeeIndexByID(const struct sEmployee *employees, int size, int id)
{
    for(int i=0; i<size; i++)
    {
        if(id == (employees+i)->ID)
        {
            return i;
        }
    }
    return -1;
}

void displayAllEmployees(const struct sEmployee *employees, int size)
{
    int No_Users=1;
    for(int i=0; i<size; i++)
    {
        if(employees[i].ID!=-1)
        {
            printf("\n\n\nEmployee %d informations:\n", i+1);
            printf("\nID = %d", employees[i].ID);
            printf("\nName = %s", employees[i].Name);
            printf("\nSalary = %f\n\n", employees[i].Salary);
            No_Users=0;
        }
    }
    if(No_Users==1) // If No_Users remains 1, no employees were found
        printf("No Employees data exist in system, please add Employees by choosing New\n");
}

void displayEmployeeByID(const struct sEmployee *employees, int size)
{
    system("cls");
    int Display_ID=0;

    printf("Please enter the employee ID : ");
    scanf("%d", &Display_ID);

    int IndexToDisplay = findEmployeeIndexByID(employees, size, Display_ID);

    if (IndexToDisplay!=-1)
    {
        printf("\n\n\nEmployee %d informations:\n", IndexToDisplay+1);
        printf("\nID = %d", employees[IndexToDisplay].ID);
        printf("\nName = %s", employees[IndexToDisplay].Name);
        printf("\nSalary = %f\n\n", employees[IndexToDisplay].Salary);
    }
    else
    {
        printf("\n\n\nThere are no employees with ID = %d", Display_ID);
    }
}

int findEmployeeIndexByName(const struct sEmployee *employees, int size, const char *name)
{
    for(int i=0; i<size; i++)
    {
        if(strcmp(name, employees[i].Name)==0)
        {
            return i;
        }
    }
    return -1;
}


void displayEmployeeByName(const struct sEmployee *employees, int size)
{
    system("cls");
    char Display_Name[30];

    printf("Please enter the employee name : ");
    _flushall();
    scanf("%s", Display_Name);

    int IndexToDisplay = findEmployeeIndexByName(employees, size, Display_Name);

    if (IndexToDisplay!=-1)
    {
        printf("\n\n\nEmployee %d informations:\n", IndexToDisplay+1);
        printf("\nID = %d", employees[IndexToDisplay].ID);
        printf("\nName = %s", employees[IndexToDisplay].Name);
        printf("\nSalary = %f\n\n", employees[IndexToDisplay].Salary);
    }
    else
    {
        printf("\n\n\nThere are no employees with Name = %s", Display_Name);
    }
}


int main()
{
    char Menu[5][10]={"New", "Edit", "Display", "Delete", "Exit"};
    int Option=0;
    int Flag=0;
    char Input;


    char NewSubMenu[3][10]={"Account", "Image", "Profile"};
    char DisplaySubMenu[3][20]={"Display All", "Display by ID", "Display by Name"};
    int SubOption=0;
    int SubFlag=0;
    char SubInput;

    int Size = getEmployeeCount();

    struct sEmployee *ptr = (struct sEmployee*) malloc(Size * sizeof(struct sEmployee));


    if(ptr!=NULL)
    {
        initializeEmployees(ptr, Size);


        do
        {
            MainMenu(Option, Menu);

        Input=_getch();
        switch (Input)
        {
        case -32:
            Input=_getch();
            switch (Input)
            {
            case 72://up
                Option--;
                if(Option<0)
                    Option=4;
                break;
            case 80://down
                Option++;
                if(Option>4)
                    Option=0;
                break;
            case 71://home
                Option=0;
                break;
            case 79://end
                Option=4;
                break;
            case 77://right
                if (Option==2)
            {
                do
                {
                    SubFlag=0;

                    SubMenu(SubOption, Option, DisplaySubMenu);

                    SubInput=_getch();
                    switch (SubInput)
                    {
                    case -32:
                        SubInput=_getch();
                        switch (SubInput)
                        {
                        case 72://up
                            SubOption--;
                            if(SubOption<0)
                                SubOption=2;
                            break;
                        case 80://down
                            SubOption++;
                            if(SubOption>2)
                            SubOption=0;
                            break;
                        case 71://home
                            SubOption=0;
                            break;
                        case 79://end
                            SubOption=2;
                            break;
                        case 75://left
                            system("cls");
                            SubOption=0;
                            SubFlag=1;
                            break;
                        }
                        break;
                    case 13://enter
                        {
                            system("cls");

                            if(SubOption==0)//display all
                            {
                                displayAllEmployees(ptr, Size);
                            }
                            else if(SubOption==1)//display by ID
                            {
                                displayEmployeeByID(ptr, Size);
                            }
                            else//display by name
                            {
                                displayEmployeeByName(ptr, Size);
                            }

                            printf("\n\n\n\nPress any key to return to the main menu");

                            Option=0;
                            SubOption=0;
                            SubFlag=1;

                            _getch();
                        break;
                        }
                    case 27:
                        SubFlag=1;
                        SubOption=0;
                        break;
                    }

                }while(SubFlag==0);
            }
            break;

            }
            break;

        case 13://enter
                if (Option==2)//Display Option
            {
                    do
                {
                    SubFlag=0;

                    SubMenu(SubOption, Option, DisplaySubMenu);

                    SubInput=_getch();
                    switch (SubInput)
                    {
                    case -32:
                        SubInput=_getch();
                        switch (SubInput)
                        {
                        case 72://up
                            SubOption--;
                            if(SubOption<0)
                                SubOption=2;
                            break;
                        case 80://down
                            SubOption++;
                            if(SubOption>2)
                            SubOption=0;
                            break;
                        case 71://home
                            SubOption=0;
                            break;
                        case 79://end
                            SubOption=2;
                            break;
                        case 75://left
                            system("cls");
                            SubOption=0;
                            SubFlag=1;
                            break;
                        }
                        break;
                    case 13://enter
                        {
                            system("cls");

                            if(SubOption==0)//display all
                            {
                                displayAllEmployees(ptr, Size);
                            }
                            else if(SubOption==1)//display by ID
                            {
                                displayEmployeeByID(ptr, Size);
                            }
                            else//display by name
                            {
                                displayEmployeeByName(ptr, Size);
                            }

                            printf("\n\n\n\nPress any key to return to the main menu");

                            Option=0;
                            SubOption=0;
                            SubFlag=1;

                            _getch();
                        break;
                        }
                    case 27:
                        SubFlag=1;
                        SubOption=0;
                        break;
                    }

                }while(SubFlag==0);
            }

            else if(Option==0)//New Option
            {
                do
                {
                    do
                    {
                        system("cls");
                        int Index;
                        if(Size==1)
                            Index=0;
                        else
                        {
                            printf("Enter the index of the employee (from 1 to %d) : ", Size);
                            scanf("%d", &Index);
                        }
                    }while(Index<1 || Index>Size);

                        if(ptr[Index-1].ID!=-1)
                        {
                            Index=-1;
                            printf("Index is occupied by another employee");
                            getch();
                        }
                }while(Index==-1);


                printf("\nPlease enter Employee %d data:\n", Index);
                int ID_Used=0;
                do
                {
                    printf("ID = ");
                    scanf("%d", &ptr[Index-1].ID);
                        ID_Used=0;
                        for(int i=0; i<Size; i++)
                        {
                            if(i==Index-1)
                                continue;
                            if(ptr[Index-1].ID==ptr[i].ID && ptr[i].ID!=-1)
                                {
                                    printf("ID is Taken, Enter another Id\n\n");
                                    ID_Used=1;
                                    break;
                                }
                        }
                }while(ID_Used==1);


                printf("First Name = ");
                _flushall();
                gets(ptr[Index-1].Name);

                printf("Salary = ");
                scanf("%f", &ptr[Index-1].Salary);

                printf("\n\n\nEmployee with ID = %d has been added successfully", ptr[Index-1].ID);
                printf(", press any key to return to the main menu");
                getch();

            }
            else if(Option==1)//Edit
            {
                    system("cls");
                    int Edit_ID=0;

                    printf("Please enter the employee ID : ");
                    scanf("%d", &Edit_ID);

                    int IndexToEdit = findEmployeeIndexByID(ptr, Size, Edit_ID);

                    if (IndexToEdit!=-1)
                    {
                        printf("\nPlease enter the Employee's data:\n");

                        printf("First Name = ");
                        _flushall();
                        gets(ptr[IndexToEdit].Name);

                        printf("Salary = ");
                        scanf("%f", &ptr[IndexToEdit].Salary);

                        printf("\n\n\nEmployee's data with ID = %d has been edited successfully", Edit_ID);
                        printf(", press any key to return to the main menu");
                        getch();

                    }
                    else
                    {
                        printf("\n\n\nThere are no employees with ID = %d, press any key to return to the main menu", Edit_ID);
                        getch();
                    }

                    Option=0;
            }
            else if(Option==3)//delete
            {
                        system("cls");
                        int Delete_ID=0;

                        printf("Please enter the employee ID : ");
                        scanf("%d", &Delete_ID);

                        int IndexToDelete = findEmployeeIndexByID(ptr, Size, Delete_ID);

                        if (IndexToDelete!=-1)
                        {
                            ptr[IndexToDelete].ID=-1;

                            printf("\n\n\nEmployee with ID = %d has been deleted successfully", Delete_ID);
                            printf(", press any key to return to the main menu");
                            getch();

                        }
                        else
                        {
                            printf("\n\n\nThere are no employees with ID = %d, press any key to return to the main menu", Delete_ID);
                            getch();
                        }

                        Option=0;

            }
            else//Exit Option
                {
                    Flag=1;
                }
            break;
        case 27:
            Flag=1;
            break;
        }

        }while(Flag==0);

        free(ptr);
    }
    else
    {
        printf("Memory allocation failed!\n");
        return 1; // Indicate error
    }

    return 0;
}