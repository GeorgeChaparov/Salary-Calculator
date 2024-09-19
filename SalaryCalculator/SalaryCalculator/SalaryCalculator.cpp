#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//Задание:
//  За група от работници в цех за торти са зададени име, ЕГН, номер на работник в цеха, 
//заплатите от последните 12 месеца (те се различават в зависимост от това кой колко поръчки е 
//изпълнил и как се е справил) и средната заплата, която са получили за последните 12 месеца.
// 
// Да се създаде програма, използваща подпрограми за : 
// 
//     • Създаване на файл с информация за работниците, без да се въвежда средена заплата; 
//     • Изчисляване на средната заплата на всеки един от работниците и запис във файла;  
//     • Извеждане на номерата на работниците, имената им и средната им заплата, за всеки работник, 
//       който е поне 1000лв. за заплата през последните 12 месеца.

//Task:
//  For a group of workers in a cake shop, name, social security number, shop worker number,
//wages from the last 12 months(they differ depending on how many orders have been completed 
//and how well) and the average salary, which are received for the last 12 months.
// 
// To create a program using subroutines for:
//
//     • Create a worker information file without entering an average salary;
//     • Calculation of the average salary of each of the workers and record in the file;
//     • Display the numbers of the workers, their names and their average salary, for each worker,
//       which is at least BGN 1000. for salary in the last 12 months.

struct Worker
{
    char workerId[10];
    char name[51];
    char EGN[11];
    int averageSalary;
};

int const FILE_NAME_SIZE = 51;

void CreateEmployee(char fileName[FILE_NAME_SIZE]);
void ReadEmployees(char fileName[FILE_NAME_SIZE]);
void MainMenu();
void RenameFile(char fileName[FILE_NAME_SIZE]);
bool IsInputOnlyDigits(char buffer[FILE_NAME_SIZE], int bufferLen);
void CreateFile(char fileName[FILE_NAME_SIZE]);
void DeleteFile(char fileName[FILE_NAME_SIZE]);
void PrintEmployees(Worker worker);
void EditWorkerId(Worker* workerToEdit);
void EditEmployee(char fileName[FILE_NAME_SIZE]);
void EditWorkerName(Worker* workerToEdit);
void EditWorkerEGN(Worker* workerToEdit);
void ReadEmployees(char fileName[FILE_NAME_SIZE]);
void WorkersWith1000Average(char fileName[FILE_NAME_SIZE]);

char m_Buffer[FILE_NAME_SIZE];

FILE* f;
Worker worker;

void main()
{
    char fileName[FILE_NAME_SIZE];

    system("CLS");
    printf("---------- Choosing File ----------\n");

    printf("\nWhat is the name of the file that you want to work with: ");
    fgets(fileName, 52, stdin);
    fileName[strlen(fileName) - 1] = '\0';

    CreateFile(fileName);

    while (true)
    {
        MainMenu();
    } 
}

void MainMenu(char fileName[FILE_NAME_SIZE])
{   
    system("CLS");
    printf("---------- Main Menu (File name: %s) ----------\n", fileName);
    printf("\n1 - Rename file");
    printf("\n2 - Delete file");
    printf("\n3 - Create employee");
    printf("\n4 - Read employees");
    printf("\n5 - Edit employee");
    printf("\n6 - Delete employee");
    printf("\n7 - Read employees wint 1000lv. average salary");
    printf("\n0 - Exit");
       
    printf("\n\nEnter the number of the command that you want to execute: "); 
    fgets(m_Buffer, 52, stdin);
    int len = strlen(m_Buffer);

    if (len > 2 || m_Buffer[0] == '\n' || !IsInputOnlyDigits(m_Buffer, len))
    {
        printf("\nYou have to input one digit!");
        fgetc(stdin);
        return;
    }
    
    m_Buffer[len - 1] = '\0';


    int input = atoi(m_Buffer);
    switch (input)
    {
    case 0:
        exit(0);
        break;
    case 1:
        RenameFile(fileName);
        break;
    case 2:
        DeleteFile(fileName);
        break;
    case 3:
        CreateEmployee(fileName);
        break;
    case 4:
        system("CLS");
        printf("---------- Read Employees ----------\n\n");
        ReadEmployees(fileName);
        getc(stdin);
        break;
    case 5:
        EditEmployee(fileName);
        break;
    case 6:

        break;
    case 7:
        WorkersWith1000Average(fileName);
        break;

    default:
        printf("\nThere is not a command with this number!");
        fgetc(stdin);
        break;
    }
}

bool FileExists(char fileName[FILE_NAME_SIZE])
{
    if (f = fopen(fileName, "r"))
    {
        fclose(f);
        return true;
    }
    return false;
}

void CreateFile(char fileName[FILE_NAME_SIZE])
{
    bool hasCorrectInput = false;

    while (hasCorrectInput == false)
    {
        system("CLS");
        printf("---------- Creating File ----------\n");
      
        if (FileExists(fileName))
        {
            printf("\nFile with this name already exist. Do you want to override it ( yes / no ) : ");
            fgets(m_Buffer, 52, stdin);
            m_Buffer[strlen(m_Buffer) - 1] = '\0';

            if (strcmp(m_Buffer, "yes") == 0 || strcmp(m_Buffer, "Yes") == 0 || strcmp(m_Buffer, "YES") == 0 || strcmp(m_Buffer, "y") == 0 || strcmp(m_Buffer, "Y") == 0)
            {
                f = fopen(fileName, "w+b");
                fclose(f);

                hasCorrectInput = true;
            }
            else if (strcmp(m_Buffer, "no") == 0 || strcmp(m_Buffer, "No" ) == 0 || strcmp(m_Buffer, "NO") == 0 || strcmp(m_Buffer, "n") == 0 || strcmp(m_Buffer, "N") == 0)
            {
                MainMenu();
                return;
            }
            else
            {
                printf("\n\nYou have to enter \"yes\" or \"no\"!");
                getc(stdin);
                continue;
            }       
        }

        f = fopen(fileName, "w+b");
        fclose(f);

        hasCorrectInput = true;

    }

    printf("\n\nThe file with name %s was created successfully!", fileName);
    getc(stdin);
}

void RenameFile(char fileName[FILE_NAME_SIZE])
{
    system("CLS");
    printf("---------- Renaming File ----------\n");

    char newName[51];
    printf("What is the new name of the file: ");
    fgets(newName, 52, stdin);
    newName[strlen(newName) - 1] = '\0';

    if (rename(fileName, newName) == 0)
    {
        printf("\n\nThe operation was successful!");
        getc(stdin);
    }
    else
    {
        printf(" \n\nSomething went wrong");
        getc(stdin);
    }
}

void DeleteFile(char fileName[FILE_NAME_SIZE])
{
    system("CLS");
    printf("---------- Deleting File ----------\n");

    if (remove(fileName) == 0)
    {
        printf("\nThe operation was successful!");
        exit(0);
    }
    else
    {
        printf(" \nSomething went wrong");
        getc(stdin);
    }
}

void CreateEmployee(char fileName[FILE_NAME_SIZE])
{
    int GetAvarageSalary(Worker worker);

    Worker bufferWorker;
    system("CLS");
    printf("---------- Creating Employee ----------\n\n");

    char numOfEmployees[51];

    printf("How many employees do you want to create: ");
    fgets(numOfEmployees, 52, stdin);
    int len = strlen(numOfEmployees);

    if (!IsInputOnlyDigits(numOfEmployees, len))
    {
        printf("\nYou have to input only digits!");
        fgetc(stdin);
        return;
    }
    else if (len > 2 || m_Buffer[0] == '\n')
    {
        printf("\nYou have to enter something!");
        fgetc(stdin);
        return;
    }

    for (int i = 0; i < atoi(numOfEmployees); i++)
    {
        int len = 0;

        bool hasName = false;
        while (!hasName)
        {
            system("CLS");
            if (atoi(numOfEmployees) != 1)
            {
                printf("---------- Name of employee number %d ----------\n", i + 1);
                printf("\nWhat is the name of employee number %d: ", i + 1); 
                fgets(m_Buffer, 52, stdin);
            }
            else
            {
                printf("---------- Name of employee ----------\n");
                printf("\nWhat is the name of the employee: "); 
                fgets(m_Buffer, 52, stdin);
            }
                       
            len = strlen(m_Buffer);

            if (len > 51)
            {
                printf("\nThe name should not be more then 50 symbols!");
                fgetc(stdin);
                continue;
            }
            else if (m_Buffer[0] == '\n')
            {
                printf("\nYou have to enter something!");
                fgetc(stdin);
                continue;
            }
            
            m_Buffer[len - 1] = '\0';
            strcpy(worker.name, m_Buffer);
            hasName = true;
        }

        bool EGN = false;
        while (!EGN)
        {
            system("CLS");
            printf("---------- The EGN of %s ----------\n", worker.name);

            printf("\nWhat is the EGN of %s: ", worker.name); 
            fgets(m_Buffer, 52, stdin);
            len = strlen(m_Buffer);

            if (len > 11 || len < 11)
            {
                printf("\nThe EGN should be 10 digits!");
                fgetc(stdin);
                continue;
            }
            
            if (!IsInputOnlyDigits(m_Buffer, len))
            {
                printf("\nThe EGN should not contain something different the digits!");
                fgetc(stdin);
                continue;
            }

            f = fopen(fileName, "rb");

            fread(&bufferWorker, sizeof(bufferWorker), 1, f);

            bool hasWorkerId = false;

            m_Buffer[len - 1] = '\0';
            while (!feof(f))
            {
                if (strcmp(m_Buffer, bufferWorker.EGN) == 0)
                {
                    printf("There is already worker with this ID!");
                    fgetc(stdin);
                    hasWorkerId = true;
                    break;
                }

                fread(&bufferWorker, sizeof(bufferWorker), 1, f);
            }

            if (hasWorkerId == true)
            {
                continue;
            }

            strcpy(worker.EGN, m_Buffer);

            EGN = true;
        }

        bool hasWorkerId = false;
        while (!hasWorkerId)
        {
            system("CLS");
            printf("---------- The worker ID of %s ----------\n", worker.name);

            printf("\nWhat is the worker ID of %s: ", worker.name); 
            fgets(m_Buffer, 52, stdin);
            len = strlen(m_Buffer);

            if (len > 10 || len < 2)
            {
                printf("\nThe worker ID can not be more then 9 digits and less then 1 digit!");
                fgetc(stdin);
                continue;
            }

            if (!IsInputOnlyDigits(m_Buffer, len))
            {
                printf("\nThe worker ID should not contain something different then digits!");
                fgetc(stdin);
                continue;
            }

            f = fopen(fileName, "rb");

            fread(&bufferWorker, sizeof(bufferWorker), 1, f);

            bool isIdPresent = false;

            m_Buffer[len - 1] = '\0';
            while (!feof(f))
            {
                if (strcmp(m_Buffer, bufferWorker.workerId) == 0)
                {
                    printf("There is already worker with this ID!");
                    fgetc(stdin);
                    isIdPresent = true;
                    break;
                }

                fread(&bufferWorker, sizeof(bufferWorker), 1, f);
            }

            if (isIdPresent == true)
            {
                continue;
            }
            
            strcpy(worker.workerId, m_Buffer);

            hasWorkerId = true;
        }
       
        worker.averageSalary = GetAvarageSalary(worker);

        
        f = fopen(fileName, "ab");
        fwrite(&worker, sizeof(worker), 1, f);
        fclose(f);
    }
}

void ReadEmployees(char fileName[FILE_NAME_SIZE])
{  
    printf("All employees in the file:\n\n");

    f = fopen(fileName, "rb");

    fread(&worker, sizeof(worker), 1, f);

    while (!feof(f))
    {
        PrintEmployees(worker);
        fread(&worker, sizeof(worker), 1, f);
    }
}

void PrintEmployees(Worker worker)
{
    printf("\t\t\t%s - %s, Average salary: %d\n",worker.workerId, worker.name, worker.averageSalary);
}

void EditEmployee(char fileName[FILE_NAME_SIZE])
{
    system("CLS");
    printf("---------- Edit Employees ----------\n");

    char workerToEdit[51];

    ReadEmployees(fileName);

    printf("Which employee do you wand to edit: "); 
    fgets(workerToEdit, 52, stdin);

    int len = strlen(workerToEdit);

    if (len > 2 || workerToEdit[0] == '\n' || !IsInputOnlyDigits(workerToEdit, len))
    {
        printf("\nYou have to input one digit!");
        _fgetchar();
        return;
    }

    workerToEdit[len - 1] = '\0';

    f = fopen(fileName, "r+b");

    //fread(&worker, sizeof(worker), 1, f);
    while (!feof(f))
    {
        fread(&worker, sizeof(worker), 1, f);
        if (strcmp(worker.workerId, workerToEdit) == 0)
        {
            printf("\n1 - Edit %s\'s name", worker.name);
            printf("\n2 - Edit %s\'s EGN", worker.name);
            printf("\n3 - Edit %s\'s worker ID", worker.name);

            printf("\n\nEnter the number of the command that you want to execute: ");
            fgets(m_Buffer, 52, stdin);
            int len = strlen(m_Buffer);

            if (len > 2 || m_Buffer[0] == '\n' || !IsInputOnlyDigits(m_Buffer, len))
            {
                printf("\nYou have to input one digit!");
                fgetc(stdin);
                return;
            }

            m_Buffer[len - 1] = '\0';

            int input = atoi(m_Buffer);
            switch (input)
            {
            case 0:
                exit(0);
                break;
            case 1:
                EditWorkerName(&worker);
                break;
            case 2:
                EditWorkerEGN(&worker);
                break;
            case 3:
                EditWorkerId(&worker);
                break;
            default:
                printf("\nThere is not a command with this number!");
                _fgetchar();
                break;
            } 
        } 
    }

    fclose(f);
}

void EditWorkerName(Worker *workerToEdit)
{
    system("CLS");
    printf("---------- Edit %s\'s name ----------\n", workerToEdit->name);

    char newName[51];

    printf("What is the new name of %s : ", workerToEdit->name);
    fgets(newName, 52, stdin);

    newName[strlen(newName) - 1] = '\0';

    strcpy(workerToEdit->name, newName);

    fseek(f, -(long)sizeof(workerToEdit), SEEK_CUR);
    fwrite(&workerToEdit, sizeof(workerToEdit), 1, f);
}

void EditWorkerEGN(Worker *workerToEdit)
{
    system("CLS");
    printf("---------- Edit %s\'s EGN ----------\n", workerToEdit->name);

    char newEGN[51];

    printf("What is the new EGN of %s (Old EGN: %s): ", workerToEdit->name, workerToEdit->EGN);
    fgets(newEGN, 52, stdin);

    int len = strlen(newEGN);
    newEGN[len - 1] = '\0';

    strcpy(workerToEdit->EGN, newEGN);

    fseek(f, -(long)sizeof(workerToEdit), SEEK_CUR);
    fwrite(&workerToEdit, sizeof(workerToEdit), 1, f);
}

void EditWorkerId(Worker* workerToEdit)
{
    system("CLS");
    printf("---------- Edit %s\'s worker ID ----------\n", workerToEdit->name);

    char newId[51];
    
    printf("What is the new worker ID of %s (Old worker ID: %s): ", workerToEdit->name, workerToEdit->workerId);
    fgets(newId, 52, stdin);

    int len = strlen(newId);
    newId[len - 1] = '\0';

    strcpy(workerToEdit->workerId, newId);

    fseek(f, -(long)sizeof(workerToEdit), SEEK_CUR);
    fwrite(&workerToEdit, sizeof(workerToEdit), 1, f);
}

void DeleteWorker()
{

}

int GetAvarageSalary(Worker worker)
{
    system("CLS");
    printf("---------- The salary of %s ----------\n", worker.name);

    int S = 0;
    for (int i = 0; i < 12; i++)
    {
        bool salary = false;
        while (!salary)
        {
            printf("\nWhat is the salary of %s for mounth %d: ", worker.name, i + 1); 
            fgets(m_Buffer, 52, stdin);
            int len = strlen(m_Buffer);

            #pragma region Проверки
            if (len > 11 || len < 2)
            {
                printf("\nThe salary should be between 1 and 9 digits!\n\n");
                _fgetchar();
                continue;
            }

            if (!IsInputOnlyDigits(m_Buffer, len))
            {
                printf("\nThere have to be only digits!\n\n");
                _fgetchar();
                continue;
            }
            #pragma endregion

            S += atoi(m_Buffer);

            salary = true;
        }        
    }

    S /= 12;

    return S;
}

bool IsInputOnlyDigits(char buffer[FILE_NAME_SIZE], int bufferLen)
{
    int br = 0;
    for (int i = 0; i < bufferLen - 1; i++)
    {
        if (buffer[i] >= '0' && buffer[i] <= '9')
        {
            br++;
        }
    }

    if (br != bufferLen - 1)
    {
        return false;
    }

    return true;
}

void WorkersWith1000Average(char fileName[FILE_NAME_SIZE])
{
    f = fopen(fileName, "rb");
    fread(&worker, sizeof(worker), 1, f);
    while (!feof(f))
    {
        if (worker.averageSalary >= 1000)
        {
            printf("\t\t\t%s - %s, Average salary: %d\n", worker.workerId, worker.name, worker.averageSalary);
        }
        fread(&worker, sizeof(worker), 1, f);
    }

    getc(stdin);
    fclose(f);
}