#include <cassert>
#include <iostream>
#include <vector>
#include <sstream>
#include <istream>
#include <ostream>
#include <algorithm>
using namespace std;

enum directions {// Defined enums for directions for use in a switch statement
		 north,
		 south,
		 east,
		 west,
		 northwest,
		 northeast,
		 southeast,
		 southwest
};

directions hashit (std::string const&);// needed for using a switch statement with strings and the directions
bool vector_contains(vector<string>,string);
vector<string> string_to_vector(string);// converts string into vector deliminates by spaces
vector<string> expand_direction(vector<string>);// if a n b is given it will try to add b s a if it doesn't already exist
vector<string> expand_generational(vector<string>);// if a n b and c s b is given c s a should be added ect... 
vector<string> break_apart_directions(vector<string>); //converts a nw b to a n b and a w b
bool valid_or_not(vector<string>);// reads list of directions and looks for contraditions.
bool test_is_valid(vector<string>);// Just calls all the above functions to solve the problem


int main()
{
  
  std::vector<string> testcase1;
  testcase1.push_back("a n b");
  testcase1.push_back("b ne c");
  testcase1.push_back("c n a");

  std::vector<string> testcase2;
  testcase2.push_back("a nw b");
  testcase2.push_back("a n c");
  
  auto output = string_to_vector(testcase1[0]);
  
  cout<<"test 1 is ";
  if(test_is_valid(testcase1)){
    cout<<"true"<<endl;
  }else{
    cout << "false"<<endl;
  }

  cout<<"test 2 is ";
  if(test_is_valid(testcase1)){
    cout<<"true"<<endl;
  }else{
    cout << "false"<<endl;
  }
  
  return 0;
}

vector<string> string_to_vector(string input) {
  vector<string> output;
  stringstream s(input);
  string out;
  while (s >> out)
    output.push_back(out);

  return output;

};
string opposite_direction(string input){
  switch(hashit(input)){
  case north:
    return string("s");
    break;
  case south:
    return string("n");
    break;
  case east:
    return string("w");
    break;
  case west:
    return string("e");
    break;
   
  }
  return string("n");
};

vector<string> break_apart_directions(vector<string> input) {
  vector<string> returnvector;
  for(auto it = input.begin() ; it < input.end(); it++){
    auto expanded = string_to_vector(*it);
    switch(hashit(expanded[1])) {
	case northeast:
	  returnvector.push_back(expanded[0]+ " n "+expanded[2]);
	  returnvector.push_back(expanded[0]+ " e "+expanded[2]);
	  break;
	case northwest:
	  returnvector.push_back(expanded[0]+ " n "+expanded[2]);
	  returnvector.push_back(expanded[0]+ " w "+expanded[2]);
	  break;
	case southeast:
	  returnvector.push_back(expanded[0]+ " s "+expanded[2]);
	  returnvector.push_back(expanded[0]+ " e "+expanded[2]);
	  break;
	case southwest:
 	  returnvector.push_back(expanded[0]+ " s "+expanded[2]);
	  returnvector.push_back(expanded[0]+ " w "+expanded[2]);
	  break;
	default:
	  returnvector.push_back(*it);
    }
  }

    return returnvector;
  
}

vector<string> expand_direction(vector<string> input){

  vector<string> vectorbuilder;
  for(auto it = input.begin(); it < input.end(); it++){
    auto middle = string_to_vector(*it);
    string space = string(" ");
    string push_string = middle[2] +space+ opposite_direction(middle[1])+space+middle[0];
    if(!vector_contains(vectorbuilder,push_string) && !vector_contains(input,push_string)){
      vectorbuilder.push_back(middle[2] +space+ opposite_direction(middle[1])+space+middle[0]);
    }
  }
  vector<string> output;
  output.reserve(input.size()+vectorbuilder.size());
  output.insert(output.end(),vectorbuilder.begin(),vectorbuilder.end());
  output.insert(output.end(),input.begin(),input.end());
  return output;

};

vector<string> expand_generational(vector<string> input){
  vector<string> vectorbuilder;
  
  for(auto it = input.begin(); it < input.end(); it++){
    auto current = *it;
    auto splitcurrent = string_to_vector(current);
    for(auto jit = input.begin(); jit < input.end(); jit++){
      if(*jit != current){// Not looking at curent value;
	auto jcurrent = *jit;
	auto jsplit = string_to_vector(*jit);
	if(jsplit[0] == splitcurrent[0]){
	  if(splitcurrent[1] == opposite_direction(jsplit[1])){
	    string push_string = string(string(jsplit[2]+ " " +  opposite_direction(jsplit[1])+" "+ splitcurrent[2]));
	    if(!vector_contains(vectorbuilder,push_string) && !vector_contains(input,push_string)){
	      vectorbuilder.push_back(push_string);
	    }
	  }
	}

      }
    }
  }
  
  vectorbuilder.insert(vectorbuilder.end(),input.begin(),input.end());
  return vectorbuilder;
};

directions hashit (std::string const& input){
  if (input == "n") return north;
  if (input == "s") return south;
  if (input == "e") return east;
  if (input == "w") return west;
  if (input == "nw") return northwest;
  if (input == "ne") return northeast;
  if (input == "sw") return southwest;
  if (input == "se") return southeast;

  return north;
};
bool vector_contains(vector<string> input_vector,string input){

  if(std::find(input_vector.begin(), input_vector.end(),input) != input_vector.end()) {
    return true;
  } else{
    return false;
  }
};

bool valid_or_not(vector<string> input){
  for(auto it = input.begin(); it < input.end(); ++it){
    auto current_pos = *it;
    for(auto jit = input.begin(); jit < input.end(); ++jit){
      if(*jit != current_pos){// not looking at current value
	auto current_split = string_to_vector(current_pos);
	auto j_split = string_to_vector(*jit);
	if(current_split[0] == j_split[0] && current_split[2] == j_split[2] && opposite_direction(current_split[1]) ==  j_split[1]) { // Found a contradiction return invalid
	  return false;
	}
      }
    }
  }
  return true;
};

bool test_is_valid(vector<string> testcase){
  testcase = break_apart_directions(testcase); 
  testcase = expand_direction(testcase);
  testcase = expand_generational(testcase);
  return valid_or_not(testcase);
};
