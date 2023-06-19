//THE SLEEPING TEACHING ASSISTANT

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include<unistd.h>

#define NUM_CHAIRS 3
#define TOTAL_STUDENTS 9
#define TA_OFFICE_HOURS 0.009

pthread_mutex_t mutex;        // just inorder to access shared memory
sem_t students_semaphore;    // to intimate ta that waiting students are present
sem_t ta_semaphore;         // to wakeup ta
time_t start_time;

int waiting_students_number = 0;

pthread_t studentThreadIDs[TOTAL_STUDENTS];

void *studentThread(void *studentName)
 {
    char *name = (char *)studentName;

    if(waiting_students_number == NUM_CHAIRS)   // i.e all chairs are full
    {
        printf("%s arrives but the office is full. Will try again later.\n", name);

        // student returns after some time
        sleep(10);

        int i=(int)(name[8]);
        pthread_create(&studentThreadIDs[i], NULL, studentThread, name);
    }
    else
    {
        pthread_mutex_lock(&mutex);
        waiting_students_number++;
        pthread_mutex_unlock(&mutex);

        printf("%s enters the office and waits in the hallway.\n", name);

        // signals TA for help
        sem_post(&students_semaphore);

        // wait for TA help
        sem_wait(&ta_semaphore);
        printf("%s is getting help from the TA.\n", name);
        // Simulating constant time taken for help
        sleep(6);
        printf("%s has received help and leaves the office.\n", name);
    }
    pthread_exit(NULL);
}


void *taThread(void *taName) {
    char *name = (char *)taName;

    while (time(NULL)-start_time <= TA_OFFICE_HOURS*60*60)
    {
        sem_wait(&students_semaphore);

        pthread_mutex_lock(&mutex);
        waiting_students_number--;
         printf("%s wakes up and starts helping a student. waiting students = %d \n", name,waiting_students_number);
        pthread_mutex_unlock(&mutex);

         // TA is helping a student.
        //So he increments ta_semaphore value inorder to indicate students that he is helping(stu waits)
        sem_post(&ta_semaphore);

        // Simulating time for TA to rest before next student
        sleep(7);
    }
    printf("\nTA office hours are completed\n");
    pthread_exit(NULL);
}


int main()
{
    start_time = time(NULL);     // time(NULL) gives current time in seconds

    sem_init(&students_semaphore, 0, 0);    // indicating that there are no students for help
    sem_init(&ta_semaphore, 0, 0);
    pthread_mutex_init(&mutex , NULL);

    pthread_t taThreadID;
    pthread_create(&taThreadID, NULL, taThread, "TA");

    char studentNames[TOTAL_STUDENTS][10] = {
        "Student 1", "Student 2", "Student 3", "Student 4", "Student 5",
        "Student 6", "Student 7", "Student 8", "Student 9"
    };

    int i;

    for (i = 0; i < TOTAL_STUDENTS; i++)
    {
        pthread_create(&studentThreadIDs[i], NULL, studentThread, studentNames[i]);
        sleep(1); // Delay between student thread creations so that all students dont come at the same instant of time
    }

    pthread_join(taThreadID, NULL);


    pthread_mutex_destroy(&mutex);
    sem_destroy(&students_semaphore);
    sem_destroy(&ta_semaphore);


    return 0;
}
