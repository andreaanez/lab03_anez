//Andrea Anez 5515689
//04/23/2020

#include "Roster.h"

#include <cstdlib>
#include <fstream>
#include <cassert>

//Core things I struggled on with compileing : 
//I indexed my arrays in correctly and should have used numstudents this gave a seg fault becuase accessing a null pointer

Roster::Roster() {
  // initialize to empty array

  this->numStudents = 0;// inotalizng the number of students in the array 
  for (int i=0; i<ROSTER_MAX; i++) {
    this->students[i] = NULL;
  }

}

void Roster::resetRoster() {
 // To avoid memory leaks:
  //  Recycle memory for all allocated students on roster // since we have memory allocated on teh heap we have to go through manually and delete it 
  // WHAT does this mean 
  while (this->numStudents > 0) {
    delete this->students[this->numStudents - 1];
    this->numStudents --; // minus one 
  }

}

void Roster::addStudentsFromFile(std::string filename) {
  std::ifstream ifs; // the stream we will use for the input file
  ifs.open(filename);
  
  if (ifs.fail()) {
    std::cerr << "Could not open input file: "
	      << filename << std::endl;
    exit(2); 
  }

  // ifs is an instance of ifstream
  // ifstream inherits from istream, 
  //   i.e. ifs is-a istream

  this->addStudentsFromStream(ifs);

}

void Roster::addStudentsFromStream(std::istream &is) {

  this->resetRoster();

  std::string thisLine;
  // Try to read past the header line.
  getline(is,thisLine);
  if ( is.eof() || is.fail() ) {
    std::cerr << "Unable to read first line of input stream" << std::endl;
    exit(3);
  }

  getline(is,thisLine);
  while (  !is.eof() && !is.fail() ) {
    // If we get here, it means the most recent attempt to read succeeded!
    // So do something with thisLine
    
    Student *sPtr = new Student(thisLine); // initalizing a new student 
    this->students[this->numStudents] = sPtr;
    this->numStudents++;
    
    // try to read another line
    getline(is,thisLine);
  } // end while

}

int Roster::getNumStudents() const { 
  return numStudents; 
  }


Student Roster::getStudentAt(int index) const { 
  return *(students[index]) ; 
}

std::string Roster::toString() const {
  std::string result = "{\n";
  for(int i = 0; i<numStudents; i++){
   result += students[i]->toString(); 
   if (!(i==numStudents-1)){ // num-1 becuase of zero indexing 
     result += ",";
   }
   result += "\n";
   
  }
  result += "";

  result += "}\n";

  return result;

}
//Selection Sort 
void Roster::sortByPerm() {
  // unsorted array boundary 
  for(int i=numStudents; i>0; i--){
    sortByPermHelper(i);


  }
}

int Roster::indexOfMaxPermAmongFirstKStudents(int k) const {
  int max_index = 0; //k-1 loops 
  for (int i=1; i<k; i++) {
    if (students[i]->getPerm() > students[max_index] -> getPerm()) //students[i] > students[max_index]) compares memory adresses of the pointers not the perm numbers that we want 
      max_index = i; // we use pointer not . becuase students is pointer array 

  }
  return max_index;
}

//// swaps max perm from [0..k-1] with elem [k-1]
void Roster::sortByPermHelper(int k) {
  int max_index;
  Student* temp; // declairing a pointer to an object of type student 
  max_index = indexOfMaxPermAmongFirstKStudents(k);
    temp = students[k-1];
    students[k-1] = students[max_index];
    students[max_index] = temp;
    }
 
 
  

