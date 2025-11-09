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

void SubMenu(int SubOption, int Option, char DisplaySubMenu[3][20]);



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
        (employees+i)->ID=-1;
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
    if(No_Users==1)
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

int isIDUnique(const struct sEmployee *employees, int size, int id, int currentIndex)
{
    for(int i=0; i<size; i++)
    {
        if(i == currentIndex)
            continue;
        if(id == (employees+i)->ID && (employees+i)->ID != -1)
        {
            return 0;
        }
    }
    return 1;
}

void handleNewEmployee(struct sEmployee *employees, int size)
{
    int Index;
    int employeeArrayIndex = -1;

    do
    {
        system("cls");
        if(size==1)
            Index=1;
        else
        {
            printf("Enter the index of the employee (from 1 to %d) : ", size);
            scanf("%d", &Index);
        }

        if(Index < 1 || Index > size)
        {
            printf("Invalid index. Please enter a value between 1 and %d.\n", size);
            getch();
            Index = -1;
        }
        else
        {
            employeeArrayIndex = Index - 1;
            if(employees[employeeArrayIndex].ID != -1)
            {
                printf("Index is occupied by another employee. Please choose an empty slot.\n");
                getch();
                Index = -1;
            }
        }
    }while(Index == -1);

    printf("\nPlease enter Employee %d data:\n", Index);

    int newID;
    do
    {
        printf("ID = ");
        scanf("%d", &newID);
        if(!isIDUnique(employees, size, newID, employeeArrayIndex))
        {
            printf("ID is Taken, Enter another Id\n\n");
        }
    }while(!isIDUnique(employees, size, newID, employeeArrayIndex));

    employees[employeeArrayIndex].ID = newID;

    printf("First Name = ");
    _flushall();
    gets(employees[employeeArrayIndex].Name);

    printf("Salary = ");
    scanf("%f", &employees[employeeArrayIndex].Salary);

    printf("\n\n\nEmployee with ID = %d has been added successfully", employees[employeeArrayIndex].ID);
    printf(", press any key to return to the main menu");
    getch();
}

int handleMainMenuSelection(int *option, char Menu[5][10])
{
    char Input = _getch();
    switch (Input)
    {
    case -32:
        Input = _getch();
        switch (Input)
        {
        case 72://up
            (*option)--;
            if((*option)<0)
                (*option)=4;
            break;
        case 80://down
            (*option)++;
            if((*option)>4)
                (*option)=0;
            break;
        case 71://home
            (*option)=0;
            break;
        case 79://end
            (*option)=4;
            break;
        case 77://right
            if (*option == 2) {
                return 2;
            }
            break;
        }
        break;
    case 13://enter
        return 1;
    case 27:
        return -1;
    }
    return 0;
}


void handleEditEmployee(struct sEmployee *employees, int size)
{
    system("cls");
    int Edit_ID=0;

    printf("Please enter the employee ID : ");
    scanf("%d", &Edit_ID);

    int IndexToEdit = findEmployeeIndexByID(employees, size, Edit_ID);

    if (IndexToEdit!=-1)
    {
        printf("\nPlease enter the Employee's data:\n");

        printf("First Name = ");
        _flushall();
        gets(employees[IndexToEdit].Name);

        printf("Salary = ");
        scanf("%f", &employees[IndexToEdit].Salary);

        printf("\n\n\nEmployee's data with ID = %d has been edited successfully", Edit_ID);
        printf(", press any key to return to the main menu");
        getch();
    }
    else
    {
        printf("\n\n\nThere are no employees with ID = %d, press any key to return to the main menu", Edit_ID);
        getch();
    }
}

void handleDeleteEmployee(struct sEmployee *employees, int size)
{
    system("cls");
    int Delete_ID=0;

    printf("Please enter the employee ID : ");
    scanf("%d", &Delete_ID);

    int IndexToDelete = findEmployeeIndexByID(employees, size, Delete_ID);

    if (IndexToDelete!=-1)
    {
        employees[IndexToDelete].ID=-1;

        printf("\n\n\nEmployee with ID = %d has been deleted successfully", Delete_ID);
        printf(", press any key to return to the main menu");
        getch();
    }
    else
    {
        printf("\n\n\nThere are no employees with ID = %d, press any key to return to the main menu", Delete_ID);
        getch();
    }
}

void handleDisplayMenu(struct sEmployee *employees, int size, char DisplaySubMenu[3][20], int *option_main_menu)
{
    int SubOption=0;
    int SubFlag=0;
    char SubInput;

    do
    {
        SubFlag=0;
        SubMenu(SubOption, 2, DisplaySubMenu); // Option 2 for Display menu item

        SubInput=_getch();
        switch (SubInput)
        {
        case -32: // Arrow key or special key in submenu
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
                system("cls"); // Clear screen when returning to main menu
                SubOption=0; // Reset sub-option
                SubFlag=1; // Exit submenu loop
                break;
            }
            break;
        case 13://enter (in submenu)
            {
                system("cls");

                if(SubOption==0)//display all
                {
                    displayAllEmployees(employees, size);
                }
                else if(SubOption==1)//display by ID
                {
                    displayEmployeeByID(employees, size);
                }
                else//display by name
                {
                    displayEmployeeByName(employees, size);
                }

                printf("\n\n\n\nPress any key to return to the main menu");
                _getch(); // Wait for user acknowledgement

                // After displaying, return to main menu, reset options
                *option_main_menu = 0; // Reset main menu option to 'New'
                SubOption=0;
                SubFlag=1; // Exit submenu loop
                break;
            }
        case 27: // Escape key in submenu
            SubFlag=1; // Exit submenu loop
            SubOption=0; // Reset sub-option
            break;
        }

    }while(SubFlag==0);
}


int main()
{
    char Menu[5][10]={"New", "Edit", "Display", "Delete", "Exit"};
    int Option=0;
    int Flag=0; // Controls the main loop

    char NewSubMenu[3][10]={"Account", "Image", "Profile"};
    char DisplaySubMenu[3][20]={"Display All", "Display by ID", "Display by Name"};

    int Size = getEmployeeCount();

    struct sEmployee *ptr = (struct sEmployee*) malloc(Size * sizeof(struct sEmployee));


    if(ptr!=NULL)
    {
        initializeEmployees(ptr, Size);


        do
        {
            MainMenu(Option, Menu);

            int menuAction = handleMainMenuSelection(&Option, Menu);

            if (menuAction == -1) { // ESC key pressed
                Flag = 1; // Set flag to exit main loop
            } else if (menuAction == 2) { // Right arrow on Display option
                handleDisplayMenu(ptr, Size, DisplaySubMenu, &Option);
            } else if (menuAction == 1) { // Enter key pressed
                if(Option == 0) // New Option
                {
                    handleNewEmployee(ptr, Size);
                }
                else if(Option == 1) // Edit Option
                {
                    handleEditEmployee(ptr, Size);
                    Option=0;
                }
                else if(Option == 2) // Display Option (if ENTER pressed, not right arrow)
                {
                    handleDisplayMenu(ptr, Size, DisplaySubMenu, &Option);
                }
                else if(Option == 3) // Delete Option
                {
                    handleDeleteEmployee(ptr, Size);
                    Option=0; // After action, return to 'New' option in main menu
                }
                else if(Option == 4) // Exit Option
                {
                    Flag = 1; // Set flag to exit main loop
                }
            }

        }while(Flag==0);

    free(ptr);
    }
    else
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    return 0;
}