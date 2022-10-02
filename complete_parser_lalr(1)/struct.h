#include <vector>
#include <string>
#include<iostream>
using namespace std;

class Port{
    public:
	string name;
	int start;
	int end;
	
	Port(){
		name="";
		start=-1;
		end=-1;
	}
	void add_name(string text){
		name=text;
	}
	void add_start(int num){
		start=num;
	}
	void add_end(int num){
		end=num;
	}
	void reset(){
		name="";
		start=-1;
		end=-1;
		
	}

};


class module_instantiation{
    public:
	string module_name;
	pair <string, string> parameters;
	string instantiation_name;
	vector <pair <string , Port>> netlist;
	
	module_instantiation(): module_name(""), parameters(pair <string, string> {"", ""}), instantiation_name(""), netlist(vector < pair <string, Port>> {})
	{}
	void add_module_name( string text){
		module_name=text;
	}
	void add_parameters(string text, string value){
		parameters.first=text;
		parameters.second=value;
	}
	void add_instantiation_name(string text){
		instantiation_name=text;
	}
	void add_net(string text, Port p2){
		pair<string, Port> net(text,p2);
		netlist.push_back(net);
	
	}
	void reset(){
		module_name="";
		pair <string, string> p{"", ""};
		parameters = p;
		instantiation_name="";
		netlist.clear();
	}
	
	void print_instance(){
		cout<< "\n\tInstance Module Name: " << module_name;
		cout<<"\n\t\tParameters: " << parameters.first << "   " << parameters.second;
		cout << "\n\t\tModule Name" << instantiation_name;
	}
};



class module_header{
    public:
	string name;
	vector <Port> input_ports;
	vector <Port> output_ports;
	vector <string> wires;
	vector <module_instantiation> module_instantiations;
	
	module_header(): name(""), input_ports(vector <Port> {}), output_ports(vector <Port> {}), wires(vector <string> {}), module_instantiations(vector <module_instantiation> {})
	{}
	void add_name(string text){
		name=text;
	}
	void add_input(Port p){
	
		input_ports.push_back(p);

	}
	void add_output(Port p){
		output_ports.push_back(p);
	}
	
	void add_wire(string text){
		wires.push_back(text);
	}
	
	void add_module_instantiation(module_instantiation temp){
		module_instantiations.push_back(temp);
	}
	
	void reset(){
		name="";
		input_ports.clear();
		output_ports.clear();
		wires.clear();
		module_instantiations.clear();
	}
	
	void print_module(){
		cout<< "\nName: " << name;
		cout<< "\n\tInput Ports: ";
		for(int i=0; i<input_ports.size();i++){
			cout<< "\n\tName: "<< input_ports[i].name << "\tStart "<< input_ports[i].start << "\tEnd " << input_ports[i].end;
		}
		cout<< "\n\tOutput Ports: ";
		for(int i=0; i<output_ports.size();i++){
			cout<< "\n\tName: "<< output_ports[i].name << "\tStart "<< output_ports[i].start << "\tEnd " << output_ports[i].end;
		}
		cout<< "\n\tWires ";
		for(int i=0; i<wires.size();i++){
			cout<< "\n\tName: "<< wires[i];
		}
		cout<< "\n\tModule Instantiation " << module_instantiations.size() ;
		for(int i=0; i<module_instantiations.size();i++){
			module_instantiations[i].print_instance();
		}
	
	}

};


class parseTree{
    public:
	vector <module_header> modules;
	
	parseTree(): modules(vector <module_header> {})
	{}
	
	void add_module(module_header m){
		modules.push_back(m);
	}
	
	void print_modulelist(){
		for(int i=0; i< modules.size(); i++){
			modules[i].print_module();
		}
		cout <<"\n";
	}
};

