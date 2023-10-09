#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

//constants
int* VOO_DOO = new int(40);

//gloabl  timer
int* timer_g = new int(0);
int* boost_controller = new int(0);

class Process {
	public:
		unsigned int pid;
    unsigned int p_length;
		unsigned int p_cpu = 0;
		unsigned int p_level = 0;
		
		// constructor
		Process(unsigned int pid, unsigned int length):pid(pid),p_length(length){
				
		}
		
		bool isJobDone(){
			if (p_length <= 0) {
				return true;
			}
			return false;
		}
};
	
class Queue {
	public:
		// max time slice a process can run at a given level of queue
		unsigned int allotment;
		// length of time slice at a given level of queue
		unsigned int quantum;
		unsigned int level;
		queue<Process*>* queuePtr;
		vector<Queue*>* mlfq;	
		
// constructor
		Queue(unsigned int allotment, unsigned int quantum, unsigned int level, vector<Queue*>* mlfq): allotment(allotment), quantum(quantum), level(level), mlfq(mlfq){
			// initialize an empty queue
			queuePtr = new queue<Process*>();	
		}
		
		// demote a process to the next level
		void demote(Process* p) {
			int next_level = p->p_level + 1;
			(*mlfq)[next_level]->queuePtr->push(p);	
			// reset process fields once demoted
			p->p_level = next_level;
			p->p_cpu = 0;
		}
		
		//start running round-robin in this queue
		void run() {
			while (!queuePtr->empty() && *boost_controller < *VOO_DOO) {
				// update current running process
				Process* curr = queuePtr->front();
				if (curr->p_length < quantum) {	
					curr->p_cpu += curr->p_length;
					*timer_g += curr->p_length;	
					*boost_controller += curr->p_length;
					curr->p_length = 0;
					// print running process info
					string msg = to_string(curr->pid) + " is running on level " + to_string(level);
					cout << msg << "\n";
					cout << "remaining job length " + to_string(curr->p_length) << "\n"; 
					cout << "job cpu accumulator " + to_string(curr->p_cpu) << "\n";
					cout << "timer is " + to_string(*timer_g) << "\n";
					cout << "bc is " + to_string(*boost_controller) << "\n";
				} else {
					curr->p_cpu += quantum;
					curr->p_length -= quantum;
				// update global timer and boost controller
					*timer_g += quantum;				
					*boost_controller += quantum;
					cout << "timer is " + to_string(*timer_g) << "\n";
					cout << "bc is " + to_string(*boost_controller) << "\n";
				// print running process info
					string msg = to_string(curr->pid) + " is running on level " + to_string(level);
					cout << msg << "\n";
					cout << "remaining job length " + to_string(curr->p_length) << "\n"; 
					cout << "job cpu accumulator " + to_string(curr->p_cpu) << "\n";
				}
				// if process done or allotment over
				if (curr->isJobDone() == true) {
					queuePtr->pop();
					cout << to_string(curr->pid) + " is done at " + to_string(*timer_g) << "\n";
					delete curr;
				} else if (curr->p_cpu >= allotment){
					queuePtr->pop();
					demote(curr);
				} else{
				// otherwise, run RR
					queuePtr->pop();
					queuePtr->push(curr);
				}
			}
		}

		// destructor
		~Queue() {
			delete queuePtr;
		}
};


int main() {
	vector<Queue*>* mlfq = new vector<Queue*>;
	// create 5 queues
  // Queue(allotment, quantum, level, vector)
	
	Queue* q0 = new Queue(10,5,0,mlfq);
	Queue* q1 = new Queue(24,8,1,mlfq);
	Queue* q2 = new Queue(40,10,2,mlfq);
	Queue* q3 = new Queue(75,15,3,mlfq);
	Queue* q4 = new Queue(10000,20,4,mlfq);
	mlfq->push_back(q0);	
	mlfq->push_back(q1);
	mlfq->push_back(q2);
	mlfq->push_back(q3);
	mlfq->push_back(q4);
	
	// Process(pid,p_length)
	Process* p0 = new Process(1001,5);	
	Process* p1 = new Process(1002,10);
	Process* p2 = new Process(1003,15);
	Process* p3 = new Process(1004,20);
	Process* p4 = new Process(1005,30);
	Process* p5 = new Process(1006,200);
	//assume all processes came the same time, put all into queue 0
	q0->queuePtr->push(p0);
	q0->queuePtr->push(p1);
	q0->queuePtr->push(p2);
	q0->queuePtr->push(p3);
	q0->queuePtr->push(p4);
	q0->queuePtr->push(p5);

	while (!q0->queuePtr->empty() || !q1->queuePtr->empty() || !q2->queuePtr->empty() || !q3->queuePtr->empty() ||!q4->queuePtr->empty()){
		for (int i = 0; i < process_list.size(); i++) {
			process_list[i]->run();
		}
		cout << "Boost -----------------------------" << "\n";
		// move q1 to q0
		while (!q1->queuePtr->empty()){
			Process* iter = q1->queuePtr->front();
			q1->queuePtr->pop();
			iter->p_cpu = 0;
			iter->p_level = 0;
			q0->queuePtr->push(iter);
		}
		// move q2 to q0
		while (!q2->queuePtr->empty()){
			Process* iter = q2->queuePtr->front();
			q2->queuePtr->pop();
			iter->p_cpu = 0;
			iter->p_level = 0;
			q0->queuePtr->push(iter);
		}
		// move q3 to q0
		while (!q3->queuePtr->empty()){
			Process* iter = q3->queuePtr->front();
			q3->queuePtr->pop();
			iter->p_cpu = 0;
			iter->p_level = 0;
			q0->queuePtr->push(iter);
		}
		// move q4 to q0
		while (!q4->queuePtr->empty()){
			Process* iter = q4->queuePtr->front();
			q4->queuePtr->pop();
			iter->p_cpu = 0;
			iter->p_level = 0;
			q0->queuePtr->push(iter);
		}
		*boost_controller = 0;
	}
	return 0;
}
