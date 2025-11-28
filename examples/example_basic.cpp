#include  <array>
#include <iostream>
#include <format>
#include <string>
#include <sstream>

#include <MLTooling.h>

template<typename T>
std::string toString(const std::vector<T>& v)
{
	std::ostringstream oss;
	oss << "[";
	
	for (size_t i = 0; i < v.size(); ++i) 
	{
		oss << v[i];
		if (i + 1 < v.size()) oss << ", ";
	}

	oss << "]";
	return oss.str();
}

static void LinearRegressionExample1()
{
	//y = 7x - 14
	std::vector<std::vector<float>> xData = { {0}, {1}, {2}, {3}, {4} };
	std::vector<float> y_data = { -14, -7, 0, 7, 14 };

	Models::LinearRegressionModel model = Models::LinearRegressionModel();

	Container::Mat mat = Container::Mat(xData);

	double lr = 0.1;
	unsigned int epochs = 500;

	model.fit(mat, y_data, lr, epochs);

	// Output: 126
	std::cout << model.predict({ 20 }) << std::endl;
}

int main()
{
	LinearRegressionExample1();
}