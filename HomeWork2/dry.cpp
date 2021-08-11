template <class T>
std::vector<T> slice(std::vector<T> vec, int start, int step, int stop)
{
	if (start < 0 || start >= vec.size() || stop < 0 || stop > vec.size() || step <= 0 )
	{
		throw BadInput();
	}

	std::vector<T> new_vec;

	for (int iterator = start; iterator < stop; iterator += step)
	{
		new_vec.emplace_back(vec[iterator]);
	}

	return new_vec;
};


class A {
public:
	std::vector<std::shared_ptr<int>> values;
	A() {};
	A(const A& a);
	~A();
	A& operator=(const A& a);



	void add(int x) { values.emplace_back(new int(x)); }

};

A& A::operator=(const A& a)
{
	if (this == &a)
	{
		return *this;
	}

	A temp_copy = A(a);

	for (int iterator = 0; iterator < values.size(); iterator++)
	{
		values[iterator].reset();
	}
	
	this->values = temp_copy.values;

	return *this;
}

A::A(const A& a)
{
	for (int iterator = 0; iterator < a.values.size(); iterator++)
	{
		this->add(*a.values[iterator]);
	}
}
A::~A()
{
	for (int iterator = 0; iterator < values.size(); iterator++)
	{
		values[iterator].reset();
	}
}








