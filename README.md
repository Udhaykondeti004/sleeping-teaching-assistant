# sleeping-teaching-assistant

## Abstract
A university computer science department has a teaching assistant (TA) 
who helps undergraduate students with their programming assignments during 
regular office hours.
The TA’s office is rather small and has room for only one desk with a 
chair and computer. There are three chairs in the hallway outside the office 
where students can sit and wait if the TA is currently helping another student. 
When there are no students who need help during office hours, the TA sits at 
the desk and takes a nap. If a student arrives during office hours and finds the 
TA sleeping, the student must awaken the TA to ask for help.
If a student arrives and finds the TA currently helping another student, 
the student sits on one of the chairs in the hallway and waits. If no chairs are 
available, the student will come back at a later time.
The code that coordinates the activities of the TA and the students is 
implemented using POSIX threads, mutex locks, and semaphores.

## Introduction
Multithreading is a powerful technique that allows programs to execute multiple tasks concurrently, thereby improving performance and resource utilization. However, managing shared resources and ensuring synchronization between threads becomes crucial to maintain consistency and to avoid conflicts. The role of a teaching assistant(TA) is vital in providing academic support to students. In this project, we simulate an office where students come seeking help from the TA. The office has a limited number of chairs for students to wait, and the TA can assist only one student at a time. If all the chairs are occupied, the student must wait outside until a chair becomes available.


