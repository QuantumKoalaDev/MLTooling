#include  <array>
#include <iostream>
#include <format>
#include <string>
#include <sstream>
#include <iomanip>

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
	std::vector<float> xData = { 0.f, 1.f, 2.f, 3.f, 4.f };
	std::vector<float> y_data = { -14.f, -7.f, 0.f, 7.f, 14 };

	Models::LinearRegressionModel model = Models::LinearRegressionModel();

	Container::Mat mat = Container::Mat(5, 1, xData);

	float lr = 0.1f;
	unsigned int epochs = 500;

	model.fit(mat, y_data, lr, epochs);

	// Output: ~126
	std::cout << std::fixed << std::setprecision(8)
		<< model.predict({ 20 }) << std::endl;
}

int main()
{
	LinearRegressionExample1();
}
