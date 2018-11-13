#include "classifier.hpp"
#include <utility>
#include <vector>
#include <algorithm>

#include "digitVisualizer.hpp"
#include "data.hpp"


Classifier::Classifier(std::vector<Digit> dataSet, const int k)
: c_dataSet(std::move(dataSet))
, c_simplifiedSize(c_dataSet.front().points().size())
, c_k(k)
{
}

void Classifier::classify(const std::vector<cv::Point2f>& path)
{

	DataSet dataSet;

    // equidistant sampling
    simplify(path);

    // normalize and mirror y

	//CALCULATE THE BOUNDING BOX
	cv::Point2f topLeft = m_simplifiedPath[0];
	cv::Point2f btmRight = m_simplifiedPath[0];


	for (auto &i : m_simplifiedPath)
	{
		if (i.x <= topLeft.x)
		{
			topLeft.x = i.x;
		}
		if (i.y <= topLeft.y)
		{
			topLeft.y = i.y;
		}
		if (i.x >= btmRight.x)
		{
			btmRight.x = i.x;
		}
		if (i.y >= btmRight.y)
		{
			btmRight.y = i.y;
		}
	}
	//normalize that to 100x100 and mirror vertically
	for (auto &i : m_simplifiedPath)
	{
		i.x = ((i.x - topLeft.x) / (btmRight.x - topLeft.x)) * 100;
		i.y = 100 - ((i.y - topLeft.y) / (btmRight.y - topLeft.y)) * 100;
	}

	std::vector<Digit> digits = dataSet.read("pendigits.tra");

	std::vector<float> shortestDistance(8, 1000);
	int pointFavorite[8];

	if (m_simplifiedPath.size() == 8) 
	{
		for (auto &i : digits)
		{
			for (int j = 0; j < 8; j++)
			{
				if (shortestDistance[j] > cv::norm((cv::Vec2f)((cv::Point2f)(i.points()[j]) - m_simplifiedPath[j])))
				{
					shortestDistance[j] = cv::norm((cv::Vec2f)((cv::Point2f)(i.points()[j]) - m_simplifiedPath[j]));
					std::cout << i.label() << std::endl;
					pointFavorite[j] = i.label();
				}
			}
		}
	}
	else
	{
		std::cout << "this didnt work whoops :(";
	}

	
	
	
	
	for (auto &i : pointFavorite)
	{
		std::cout << i << std::endl;

	}



    /*~~~~~~~~~~~*
     * YOUR CODE *
     * GOES HERE *
     *~~~~~~~~~~~*/

    // match using knn

    /*~~~~~~~~~~~*
     * YOUR CODE *
     * GOES HERE *
     *~~~~~~~~~~~*/

    // you should store your result in m_result
    // m_result = ...
}

int Classifier::getResult() const
{
    return m_result;
}

std::vector<cv::Point2f> Classifier::getSimplifiedPath() const
{
    return m_simplifiedPath;
}

void Classifier::simplify(std::vector<cv::Point2f> path)
{

    // sample path with equal spacing and store in m_simplifiedPath
    // you should use c_simplifiedSize as number of points in simplified path
	m_simplifiedPath.clear();
	float length = 0;
	std::vector<cv::Vec2f> pathAsVector;
	cv::Point2f lastPoint = cv::Point2f(-1, -1);
	for (auto &i : path) 
	{
		if (lastPoint == cv::Point2f(-1, -1)) {
			lastPoint = i;
		}
		else
		{

			pathAsVector.push_back(cv::Vec2f((i - lastPoint ).x, (i - lastPoint).y));
			std::cout << pathAsVector.back() << std::endl;
			lastPoint = i;
			length += cv::norm(pathAsVector.back());
		}

	}



	length = length / c_simplifiedSize;
	std::cout << length << std::endl;
	double currentLength = length;
	cv::Vec2f currentVector = (0, 0);
	m_simplifiedPath.push_back(path[0]);
	std::cout << "start: " <<  m_simplifiedPath.back() << std::endl;

	for (auto &i : pathAsVector)
<<<<<<< HEAD
	{
		double normi = cv::norm(i);
		bool foundPoint = false;
		while (currentLength <= normi) {
			m_simplifiedPath.push_back(path[0] + cv::Point2f(currentVector) + cv::Point2f(i/normi * currentLength));
			foundPoint = true;
			i = i - (i / normi * currentLength);
=======
	{	
		if (currentLength <= cv::norm(i)) {
			m_simplifiedPath.push_back(path[0] + cv::Point2f(currentVector) + cv::Point2f(i/norm(i) * currentLength));
			pathAsVector[(&i + sizeof(i) - &pathAsVector[0])/sizeof(i)] += i - (i / norm(i) * currentLength);
>>>>>>> 30200ab81bc6e51857f6ebeca14fc7f20f647dc2
			currentLength = length;
			//std::cout << currentVector;
			std::cout << m_simplifiedPath.back() << std::endl;
			normi = cv::norm(i);
		}
		if(!foundPoint) {
			currentLength -= normi;
		}
		currentVector += i;
	}
	if (m_simplifiedPath.size() < 8) {
		m_simplifiedPath.push_back(path.back());
	}
	std::cout << "end: " <<  m_simplifiedPath.back() << std::endl;


	std::cout << "Anzahl: " << m_simplifiedPath.size() << std::endl;

	//we got 8 points

	


    /*~~~~~~~~~~~*
     * YOUR CODE *
     * GOES HERE *
     *~~~~~~~~~~~*/
}
