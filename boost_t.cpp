#include "define.h"
#include <map>
#include <string>
#include <vector>
#include <set>
#include <boost/format.hpp>
//#include <boost/filesystem.hpp>
#include <boost/optional.hpp>

using namespace std;
using namespace boost;

static void format_str()
{
   unsigned int arr[5] = { 0x05, 0x04, 0xAA, 0x0F, 0x0D };

    cout << format("%02X-%02X-%02X-%02X-%02X")
            % arr[0]
            % arr[1]
            % arr[2]
            % arr[3]
            % arr[4]
         << endl;
}

/*static void path_exist(const char *mpath)
{
	/boost::filesystem::path bpath(mpath);

	if(boost::filesystem::exists(mpath)){
		cout<<mpath<<" exist"<<endl;
	}else{
		cout<<mpath<<" not exist"<<endl;
	}
}*/
typedef map<string, string> artise_ablbum_map;
static optional<string> find_last_album_of(artise_ablbum_map &dict,
	const string &name)
{
	auto it = dict.find(name);

	if(it != dict.end()){
		return it->second;
	}else{
		return boost::none;
	}
}

class moveable
{
public:
	moveable() {}
	moveable(moveable &&other)
	{std::swap(x, other.x);}
	moveable &operator=(moveable &&other)
	{
		std::swap(x, other.x);
		return *this;
	}
	static moveable create() //factory function
	{
		moveable obj;
		return obj;
	}
private:
	int  x;
};

static void left_right_value()
{
	int x = 10;
	//left value
	int *p = &++x;
	cout<<*p<<endl;
	++x = 10;
	cout<<*p<<endl;

	int &l = ++x;

	//right value
	int &&r = x++;
	x++;
	cout<<r<<endl;
	cout<<l<<endl;

	//make use of right value
	/*moveable m1;
	moveable m2(std::move(m1));//transfer object
	moveable m3 = moveable::create();*/

	vector<string> s1;
	s1.emplace_back("back");
}

static void type_op()
{
	set<string> sset;
	sset.insert("example");
	sset.insert("instance");
	sset.insert("e.g");
	decltype(sset) sset1 = sset;

	/*for(auto it = sset1.begin(); it != sset1.end(); ++it){
		cout<<*it<<" ";
	}*/
	for(auto &s : sset1){
		//s.insert(s.end(), "(s)");
		cout<<s<<" ";
	}
	cout<<endl;
}

static auto new_func(int x) -> decltype(x)
{
	return x*2;
}


class cclass
{
public:
	//use default construct, destruct
	cclass()  = default;
	~cclass() = default;

	//forbidden copy
	cclass(const cclass &)		      = delete;
 	cclass &operator=(const cclass &) = delete;

	void set(int x)
	{ _x = x;}

	int get() const
	{return _x;}
private:
	int  _x;
};
static void new_class()
{
	cclass obj;
	obj.set(10);
	cout<<obj.get()<<endl;

	//cclass obj2 = obj;
	//cout<<obj2.get()<<endl;
}

class cbase
{
public:
	virtual ~cbase() = default;

	virtual void f() = 0;
	virtual void g() const {}
	void h() {}
	virtual void i() {}
};
class cderived : public cbase
{
public:
	virtual ~cderived() = default;

	//use override to force function have the
	// identical signture
	void f() override {}
	void g() const override {}
	//use final to disallow anymore override
	void i() override final {}
};
class cdoubledervied : public cderived
{
public:
	//void i() override {}
};
static void derive_class()
{
	cderived obj;
	obj.g();

	cdoubledervied child_obj;
}

class init_demo
{
public:
	string 		s = "init_demo";
	vector<int> vi{1,2,3};
	int         _a, _b;
	init_demo(int a, int b):_a(a),_b(b){}
	init_demo() : init_demo(0, 0) {} //委托构造函数
	init_demo(int a) : init_demo(a, 0) {}
	void print()
	{
		cout<<_a<<" "<<_b<<endl;
		cout<<s<<endl;
		for(auto i : vi){
			i += 10;
			cout<<i<<" ";
		}
		cout<<endl;
	}
};
static void init_class_member()
{
	init_demo obj(6);
	obj.print();
}

using int64 = long;
using intmap = std::map<int64, string>;

void type_demo()
{
	constexpr int kk = 1024;
	cout<<"const expression "<<kk<<endl;
	static_assert(sizeof(int)==4, "int must be 32 bit");
}

//variable parameters
template<typename ... Args>
int printm(const char *format, const Args& ... args)
{
	cout<<sizeof...(Args)<<endl;
	return printf(format, args...);
}

void variable_parameters()
{
	//lambda expr
	auto power2 = [](int x){
	return x*x;
	};
	printm("the %d day of the %d month\n", 1, 3);
	cout<<power2(5)<<endl;

	vector<int> v = {1, 3, 5, 7};
	for_each(v.begin(), v.end(), [](int &x){x*=x;});
	//work as operator()
	for_each(v.begin(), v.end(), [](int x){cout<<x<<",";});
	cout<<endl;
}

void boost_demo()
{
	/*const char *path = "./boost_t.cpp";
	path_exist(path);*/
	format_str();
	artise_ablbum_map dict = {{"music1", "man"}, {"music2", "woman"}};
	
	optional<string> opt = find_last_album_of(dict, "child");
	cout<<opt.get_value_or("none")<<endl;

	left_right_value();

	type_op();

	cout<<new_func(4)<<endl;

	new_class();

	derive_class();

	init_class_member();

	type_demo();

	variable_parameters();
}