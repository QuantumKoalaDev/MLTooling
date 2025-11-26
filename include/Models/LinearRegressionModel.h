#pragma once

#include "../Mat.h"

#include <vector>

namespace Models
{
	class LinearRegressionModel
	{
	private:
		std::vector<float> m_weights;
		double m_bias;

		void updateWeights(const std::vector<float>& weightGradients, float learningRate);
		void updateBias(float biasGradient, float learningRate);

	public:
		LinearRegressionModel();
		~LinearRegressionModel() = default;

		float predict(const std::vector<float>& xFeatures) const;
		void fit(const Mat& xData, const std::vector<float>& yData, float learningRate, unsigned int epochs);
	};
}