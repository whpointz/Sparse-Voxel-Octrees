/**
 *    > Author:   whpointz
 *    > Mail:     506273980@qq.com
 *    > Github:   https://www.github.com/whpointz
 *    > Description:
 *
 *    > Created Time: 2017/06/24 13:30:54
**/

// OpenCv 
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

//Octree
#include "Octree.hpp"
#include "Point.hpp"

//IO
#include <iostream>
#include <queue>
using namespace std;


int main(){

	Octree2d* Octree_zwh = new Octree2d;
	OctreeNode2d* Root;
	
	Root = Octree_zwh->BuildTree(Root, Depth, glm::vec2(0, 0), glm::vec2(logo.cols, logo.rows));

// 	cout << glm::to_string(Root->_min) << " " << glm::to_string(Root->_max) << endl;
// 
// 	cout << glm::to_string(Root->_children[0]->_min) << " " << glm::to_string(Root->_children[0]->_max) << endl;
// 	cout << glm::to_string(Root->_children[1]->_min) << " " << glm::to_string(Root->_children[1]->_max) << endl;
// 	cout << glm::to_string(Root->_children[2]->_min) << " " << glm::to_string(Root->_children[2]->_max) << endl;
// 	cout << glm::to_string(Root->_children[3]->_min) << " " << glm::to_string(Root->_children[3]->_max) << endl;


	printf("\n\n\n");

	//a new mat to store the ans
	char imagename[10];
	sprintf_s(imagename, "%d.jpg", Depth);
	Mat ans = logo.clone();

	//out all the data in the Octree
	queue<OctreeNode2d*> S;
	S.push(Root);
	while (!S.empty())
	{
		for (int i = 0; i < 4;i++)
		{
			if (S.front()->_children[i] != 0)
				S.push(S.front()->_children[i]);
		}

		if (S.front()->_children[0]==0)
		{
			for (int i = S.front()->_min.x; i < S.front()->_max.x; i++)
			{
				for (int j = S.front()->_min.y; j < S.front()->_max.y; j++)
				{
					if (i >= 0 && i<ans.cols && j >= 0 && j< ans.rows)
					{ 
						ans.at<Vec3b>(j, i)[0] = S.front()->_data.x;
						ans.at<Vec3b>(j, i)[1] = S.front()->_data.y;
						ans.at<Vec3b>(j, i)[2] = S.front()->_data.z;
					}
					
				}
			}
			
			//cout << glm::to_string(S.front()->_min) << " " << glm::to_string(S.front()->_max) << " " << glm::to_string(S.front()->_data) << endl;

		}
		
		S.pop();
	}

	imwrite(imagename, ans);
	imshow("logo", logo);
	waitKey();


}