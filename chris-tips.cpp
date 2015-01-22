// chris-tips.cpp : A short introduction to how to do C++ with 11 goodies
//



#include <iostream> // this lib lets me stream to std::cout (the console)
#include <memory> // this is for the safe pointer wrapper
#include <vector> 
#include <iostream> // this is for file io
#include <fstream> // file utils

// Lesson 1: Classes
// Classes are buckets for data and functions, put everything in buckets - don't litter the place with free functions

// By default all items are private so you need to qualify them as public for the outside world to see it

class vec {
	public:				// everything below here is public
		double x;
		double y;
		double z;
		vec(const double& x = 0, const double& y = 0, const double& z = 1) : x{ x }, y{ y }, z{ z } {} // This is a constructor
		// the = 0 sets a default value, the & is a reference to prevent copying for efficiency and the stuff after ":" is an optimized initialization list
		// the const modifier says "this function won't change the value", again this produces optimizations so use it as much as you can
};

// You can create aliases to types too (1_2)

using velocity = vec;
using position = vec;

// Classes can just be holders of functions without data members, this gives a function scope and allows you to define things
// some functions need to be hidden in it or break down long functions into private helpers... (1_3)

class KludgeUtils {
	public:

		static long add(const long& a, const long& b) { // the static modifier makes this function callable without an instance
			return (a + b);								// its just like a free function 
		}

		static double complex_function(const velocity& vel, const position& pos) {
			// do some calculations here
			position newpos;
			newpos.x = pos.x * vel.x; newpos.y = pos.y * vel.y;
			helper_function(newpos); // decompose large functions into private helpers
			// do more calculations
			return (newpos.x + newpos.y + newpos.z);
		}

	private:
		static void helper_function(position& pos) {
			// Modify the values and it will affect the caller values because its a reference
			pos.z = 100;
		}
};

class FudgeUtils {
public:
	// This function is almost the same as KludgeUtils::add() but its has a new scope so you can't confuse it 
	static long add(const long& a, const long& b) { // the static modifier makes this function callable without an instance
		return (a + b + 1);								// its just like a free function 
	}
};

// Lesson 2 : Pointers are dead!
// References are denoted by "&" and they act like pointers but CANNOT be null, the compiler will warn you

long num = 1234;
long& refnum = num;		// changing refnum changes num

// If you want to create an object on the heap use a wrapper std::shared_ptr<Typename> (2_1)
std::shared_ptr<position> safe = std::make_shared<position>(position{ 100, 200, 300 });

// make_shared is a utility function that does a safe "new position{}" for you and puts it in the wrapper
// that's a lot of typing so use auto to deduce the type for you
auto quick_safe = std::make_shared<position>(position{ 400, 500, 600 });

// you can now access it like a pointer (see below) and the memory will auto-delete when the wrapper goes out of scope!

// But what's it good for? putting things into collections safely (2_2)
using safe_vec = std::shared_ptr < vec > ;
std::vector<safe_vec> posvec{ std::make_shared<vec>(vec{ 1, 2, 3 }), 
	std::make_shared<vec>(vec{ 4, 5, 6 }), std::make_shared<vec>(vec{ 7, 8, 9 }), }; 
// a vector holding 3 shared pointers to vec objects on heap



int main(int argc, char** argv)
{
	std::cout << "*** Lesson 1: Classes ***" << std::endl; // I'm writing via a stream, its safe and easy. endl is newline.
	vec lesson1{ 10, 20, 30 };
	// I've just initialized a new instance with those values, the curly brackets say don't allow narrowing, get in the habit (more in later lessons)
	std::cout << "lesson1.x = " << lesson1.x << " lesson1.y = " << lesson1.y << " lesson1.z = " << lesson1.z << std::endl;
	vec lesson1_1{ 100 };
	std::cout << "lesson1_1.x = " << lesson1_1.x << " lesson1_1.y = " << lesson1_1.y << " lesson1_1.z = " << lesson1_1.z << std::endl;
	
	// Now I can use the alias type
	position lesson1_2;
	std::cout << "lesson1_2.x = " << lesson1_2.x << " lesson1_2.y = " << lesson1_2.y << " lesson1_2.z = " << lesson1_2.z << std::endl;
	// Note it got initialized by the constructor

	// Static utility functions, wrapped in classes

	std::cout << "lesson1_3 : calling KludgeUtils::add(1,2) = " << KludgeUtils::add(1, 2) << " calling FudgeUtils::add(1,2) = " << FudgeUtils::add(1, 2) << std::endl;
	// The :: is the scope resolution operator, use it to reference a static public member of a class 
	// see no instance object required

	std::cout << "lesson1_3 : calling KludgeUtils::complex_function(velocity{1,2,3}, position{10,10,10}) = " << KludgeUtils::complex_function(velocity{ 1, 2, 3 }, position{ 10, 10, 10 }) << std::endl;

	std::cout << "*** Lesson 2: Pointers are dead ***" << std::endl;
	std::cout << "lesson2 : num = " << num << " and refnum = " << refnum << std::endl;

	refnum += 1; // increment 
	std::cout << "lesson2 : now after increment num = " << num << " and refnum = " << refnum << std::endl;

	std::cout << "lesson2_1 : this is how you access wrapped safe, like a pointer (*safe).x " << (*safe).x << std::endl;
	std::cout << "lesson2_1 : can also access wrapped quick_safe, by function (quick_safe.get())->x " << (quick_safe.get())->x << std::endl;

	std::cout << "lesson2_2 : using a loop safely with a collection ..." << std::endl;

	// This form of for loop can't break and is nice an clean
	for (safe_vec value : posvec) {
		std::cout << "looking at values x, y, z with " << value->x << " " << value->y << " " << value->z << std::endl;
	}

	// and now to a file...
	std::ofstream output("localfile.txt");

	if (!output) { // check the file opened OK
		std::cerr << "error: open file for output failed!" << std::endl;
		return 1;
	}

	for (safe_vec value : posvec) {
		// the ofstream object replaces std::cout here, then its the same use
		output << "looking at values x, y, z with " << value->x << " " << value->y << " " << value->z << std::endl;
	}

	output.close(); // must close file 

	return 0;
}

