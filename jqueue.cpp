// CMSC 341 - Spring 2020 - Project 4
// JQueue: a job queue using a skew heap and function pointers

#include "jqueue.h"

using std::cout;
using std::endl;
using std::domain_error;

JQueue::JQueue(prifn_t priFn) {
  _heap = nullptr;
  _size = 0;
  priority = priFn;
}

JQueue::~JQueue() {
  destructHelp();
}

JQueue::JQueue(const JQueue& rhs) {
  priority = rhs.priority;
  _heap = copyHelper(rhs._heap);
  _size = rhs._size;
}

JQueue& JQueue::operator=(const JQueue& rhs) {
  if (this != &rhs){
    destructHelp();
    priority = rhs.priority;
    _size = rhs._size;
    copyHelper(_heap);
  }
  else{
    std::cout << "No self assignment" << std::endl;
  }
  return *this;
}

void JQueue::insertJob(const job_t& input) {
  Node* newNode = new Node (input);
  _heap = mergeHelper(_heap, newNode);
  _size++;
}

job_t JQueue::getNextJob() {
  if (_heap == nullptr){
    throw domain_error ("Can't getNextJob from an empty queue");
  }
  job_t job = _heap->_job;
  removeMax();
  _size--;
  return job;
}

void JQueue::mergeWithQueue(JQueue& rhs) {
  if (priority != rhs.priority){
    throw domain_error ("Can't merge queues with different priority functions! \n");
  }
  else{
    _heap = mergeHelper(_heap, rhs._heap);
    _size += rhs._size;
    rhs._heap = nullptr;
    rhs._size = 0;
  }
}

void JQueue::clear() {
  destructHelp();
}

int JQueue::numJobs() const {
  return _size;
}

void JQueue::printJobQueue() const {
  printPreOrder(_heap);
}

prifn_t JQueue::getPriorityFn() const {
  return priority;
}

void JQueue::setPriorityFn(prifn_t priFn) {
  JQueue ptr(priFn);
  while (_heap != nullptr){
    ptr.insertJob(_heap->_job);
    removeMax();
  }
  priority = priFn;
  _heap = copyHelper(ptr._heap);
}

void JQueue::dump() const {
  dumpHelp(_heap);
}

ostream& operator<<(ostream& sout, const job_t& job) {
  sout << "Job: " << job._name << ", pri: " << job._priority
       << ", u: " << job._user << ", g: " << job._group << ", proc: "
       << job._proc << ", mem: " << job._mem << ", time: " << job._time;
  return sout;
}

ostream& operator<<(ostream& sout, const Node& node) {
  sout << node._job;
  return sout;
}


