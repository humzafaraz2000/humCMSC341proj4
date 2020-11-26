/*
*File:    mytest.cpp 
*Author:  Humza Faraz
*Date:    04/29/20202
*E-mail:  hfaraz1@umbc.edu
*Description: Tester file for jqueue
*/

#include "jqueue.h"


int priorityFn1(const job_t &job);
int priorityFn2(const job_t &job);

int main() {

  JQueue jobQueue(priorityFn1);

  // Create some test jobs and insert them into the queue
  
  job_t testJob1("test1", 50, 3, 11,  16, 1024, 120);
  job_t testJob2("test2", 50, 7,  5, 128,  512, 300);
  job_t testJob3("test3", 20, 3,  0, 128, 1024, 1800);
  job_t testJob4("test1a", 50, 3, 11,  16, 1024, 120);

  jobQueue.insertJob(testJob3);
  jobQueue.insertJob(testJob1);
  jobQueue.insertJob(testJob2);
  jobQueue.insertJob(testJob4);
  
  // Print the queue, change priority function, print again, change
  // again, print again.  Changing the priority function should cause
  // the heap to be rebuilt.

  std::cout << std::endl;
  jobQueue.printJobQueue();
  std::cout << "Dump the queue:\n";
  jobQueue.dump();
  
  jobQueue.setPriorityFn(priorityFn2);

  std::cout << std::endl;
  jobQueue.printJobQueue();
  std::cout << "Dump the queue:\n";
  jobQueue.dump();
  
  jobQueue.setPriorityFn(priorityFn1);

  std::cout << std::endl;
  jobQueue.printJobQueue();
  std::cout << "Dump the queue:\n";
  jobQueue.dump();

  //test copy constructor
  std::cout << std::endl;
  JQueue copy(jobQueue);
  std::cout << "Print job queue of copy" << std::endl;
  copy.printJobQueue();
  std::cout << "Dump copy" << std::endl;
  copy.dump();

  //test assignment operator
  std::cout << std::endl;
  JQueue assign = jobQueue;
  std::cout << "Print job queue of assign" << std::endl;
  assign.printJobQueue();
  std::cout << "Dump assign" << std::endl;
  assign.dump(); 
  std::cout << std::endl;

  //test self-assignment
  std::cout << "Test self-assignment" << std::endl;
  assign = assign; 

  //test deep copy (should be no change to jobQueue)
  copy.getNextJob();
  jobQueue.dump();
  std::cout << std::endl;

  std::cout << "\nFinal queue in priority order:\n";
  while (jobQueue.numJobs() > 0) {
    job_t job = jobQueue.getNextJob();
    std::cout << "[" << priorityFn1(job) << "] " << job << std::endl;
  }
  
  return 0;
}

int priorityFn1(const job_t &job) {
  float pri;
  pri = 200 + job._priority;
  if (job._user == 7 || job._user == 23) pri += 200;
  if (job._group == 0 || job._group == 11) pri += 100;
  pri = pri - job._proc - 0.01*job._mem - (1.0/3600.0)*job._time;
  return int(pri);
}

int priorityFn2(const job_t&job) {
  return int(job._time);
}
