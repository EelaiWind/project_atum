#include "weight.h"

Weights::Weights(const Weights& weights, InitType type){
	if (type == COPY){
		for(int i = 0; i < weights.get_count(); i++){
			m_weights_vector.push_back( Matrix(weights.m_weights_vector[i]) );
		}
	}
	else if (type == ZEROS){
		for(int i = 0; i < weights.get_count(); i++){
			m_weights_vector.push_back( Matrix(size(weights.m_weights_vector[i]), arma::fill::zeros) );
		}
	}
	else if(type == ONES){
		for(int i = 0; i < weights.get_count(); i++){
			m_weights_vector.push_back( Matrix(size(weights.m_weights_vector[i]), arma::fill::ones) );
		}
	}
	else if(type == GAUSSIAN){
		for(int i = 0; i < weights.get_count(); i++){
			m_weights_vector.push_back( Matrix(size(weights.m_weights_vector[i]), arma::fill::randn) );
		}
	}
	else if(type == UNIFORM){
		for(int i = 0; i < weights.get_count(); i++){
			m_weights_vector.push_back( Matrix(size(weights.m_weights_vector[i]), arma::fill::randu) );
		}
	}
}

Weights::Weights(){

}

Weights::Weights(const vector<int>& model_architecture, InitType type){
	if (type == COPY){
		std::cerr << "[ERROR] weight initialization cannot use COPY mode." << std::endl;
		exit(1);
	}
	else if (type == ZEROS){
		for(int i = 0; i < model_architecture.size()-1; i++){
			m_weights_vector.push_back(zeros<Matrix>(model_architecture[i], model_architecture[i+1]));
			m_weights_vector.push_back(zeros<Matrix>(1, model_architecture[i+1]));
		}
	}
	else if(type == ONES){
		for(int i = 0; i < model_architecture.size()-1; i++){
			m_weights_vector.push_back(ones<Matrix>(model_architecture[i], model_architecture[i+1]));
			m_weights_vector.push_back(ones<Matrix>(1, model_architecture[i+1]));
		}
	}
	else if(type == GAUSSIAN){
		for(int i = 0; i < model_architecture.size()-1; i++){
			m_weights_vector.push_back(randn<Matrix>(model_architecture[i], model_architecture[i+1]));
			m_weights_vector.push_back(randn<Matrix>(1, model_architecture[i+1]));
		}
	}
	else if(type == UNIFORM){
		for(int i = 0; i < model_architecture.size()-1; i++){
			m_weights_vector.push_back(randu<Matrix>(model_architecture[i], model_architecture[i+1]));
			m_weights_vector.push_back(randu<Matrix>(1, model_architecture[i+1]));
		}
	}
}

void Weights::push_back(const Matrix &matrix)
{
	m_weights_vector.push_back(Matrix(matrix));
}

void Weights::add_weights(const Weights& weights){
	for(int i = 0; i < get_count(); i++)
		m_weights_vector[i] += weights.m_weights_vector[i];
}

void Weights::multiply_scalar(const double scalar){
	for(int i = 0; i < get_count(); i++){
		m_weights_vector[i] *= scalar;
	}
}

Weights::~Weights(){
	m_weights_vector.clear();
}
