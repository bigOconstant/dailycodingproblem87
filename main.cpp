#include <cassert>
#include <iostream>
#include <vector>
#include <sstream>
#include <istream>
#include <ostream>
using namespace std;
enum directions {
		 north,
		 south,
		 east,
		 west,
		 northwest,
		 northeast,
		 southeast,
		 southwest
};

directions hashit (std::string const&);
vector<string> string_to_vector(string);
vector<string> expand_direction(vector<string>);
vector<string> expand_generational(vector<string>);
vector<string> break_apart_directions(vector<string>); 




int main()
{
  cout << "starting app"<<endl;
  std::vector<string> testcase1;
  testcase1.push_back("a n b");
  testcase1.push_back("b ne c");
  testcase1.push_back("c n a");

  auto output = string_to_vector(testcase1[0]);

  testcase1 = break_apart_directions(testcase1); 
  testcase1 = expand_direction(testcase1);
  testcase1 = expand_generational(testcase1);

   for(auto it = testcase1.begin(); it < testcase1.end(); ++it){
    cout<<*it<<endl;
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
    vectorbuilder.push_back(middle[2] +space+ opposite_direction(middle[1])+space+middle[0]);
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
	    vectorbuilder.push_back(string(jsplit[2]+ " " +  opposite_direction(jsplit[1])+" "+ splitcurrent[2]));

	  }
	}

      }
    }
  }
  
  vectorbuilder.insert(vectorbuilder.end(),input.begin(),input.end());
  return vectorbuilder;
}

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
