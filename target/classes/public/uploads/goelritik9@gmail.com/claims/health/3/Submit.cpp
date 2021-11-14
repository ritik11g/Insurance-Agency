#include<bits/stdc++.h>
using namespace std;

struct bucket
{
	int LocalDepth=0;
	vector<int> vec;
};

void Insert(int);
void Display(void);
int Search(int);
void Delete(int);
void Split(int, bucket*);
void Merge(void);
void Shrink(void);

int GlobalDepth,BucketCapacity;
map<int,bucket*> BucketMap;


int main()
{
	cout<<"The Bucket Capacity is: "<<endl;
	cin>>BucketCapacity;
	BucketMap[0] = new bucket;
	
	int YourChoice;
	int Number;
	while(1)
	{
		cout<<"1. Insertion"<<endl;
		cout<<"2. Display"<<endl;
		cout<<"3. Search"<<endl;
		cout<<"4. Deletion"<<endl;
		cout<<"5. Exit"<<endl;
		cout<<"Enter your choice : "<<endl;
		cin>>YourChoice;
		
		switch(YourChoice)
		{
			case 1:
				cout<<"Enter the number to be inserted : "<<endl;
				cin>>Number;
				Insert(Number);
				cout<<"Number has been inserted successfully!!!!"<<endl;
				break;
			case 2:
				Display();
				break;
			case 3:
				cout<<"Enter the number to be searched : "<<endl;
				cin>>Number;
				if(Search(Number))
					cout<<"The number is present!!!!"<<endl;
				else
					cout<<"The number is not present!!!!"<<endl;
				break;
			case 4:
				cout<<"Enter the number to be deleted : "<<endl;
				cin>>Number;
				Delete(Number);
				break;
			case 5:
				exit(0);
			default:
				cout<<"Invalid Choice!!!!"<<endl;
		}
		
	}

}


void Insert(int Number)
{
	int h = Number & ((1<<GlobalDepth) - 1);

	if(BucketMap[h]->vec.size() < BucketCapacity)
	{
		BucketMap[h]->vec.push_back(Number);
	}
	else
	{
		Split(h,BucketMap[h]);
		Insert(Number);
	}
}


void Display()
{
	for(int z=0; z<(1<<GlobalDepth); ++z)
	{
		cout<<"Local depth of bucket "<<z<<" is : "<<BucketMap[z]->LocalDepth<<endl;
		
		for(auto iter = BucketMap[z]->vec.begin(); iter!=BucketMap[z]->vec.end(); ++iter)
		{
			cout<<(*iter)<<" ";
		}
		cout<<endl;
	}
}


int Search(int Number)
{
	int h = Number & ((1<<GlobalDepth) - 1);

	vector<int>::iterator iter;
	iter = find(BucketMap[h]->vec.begin(), BucketMap[h]->vec.end(),Number);
	
	return iter != BucketMap[h]->vec.end();
}



void Delete(int Number)
{
	if(Search(Number))
	{	
		for(auto z = BucketMap.begin(); z!=BucketMap.end(); ++z)
		{
			vector<int>::iterator iter;
		
			iter = find(z->second->vec.begin(), z->second->vec.end(),Number);
			
			if(iter!=z->second->vec.end())
			{
				z->second->vec.erase(iter);
				break;
			}
		}
		Merge();
		Shrink();

		cout<<"The number has been deleted successfully!!!!"<<endl;
	}
	else
	{
		cout<<"The number is not present!!!!"<<endl;;
	}
}

void Split(int SplitIndex, bucket * SplitBucket)
{
	bucket * NewBucket = new bucket;

	vector<int>temp;
	for(auto iter = SplitBucket->vec.begin(); iter!=SplitBucket->vec.end(); ++iter)
	{
		temp.push_back(*iter);
	}
	
	SplitBucket->vec.clear();
	
	if(SplitBucket->LocalDepth == GlobalDepth)
	{
		BucketMap[SplitIndex ^ (1<<GlobalDepth)] = NewBucket;
		if(GlobalDepth!=0)
		{
			for (int z = 0; z < (1<<GlobalDepth); ++z)
			{
				if(z!=SplitIndex)
				{
					BucketMap[z ^ (1<<GlobalDepth)] = BucketMap[z];
				}
			}
		}

		GlobalDepth++;
		SplitBucket->LocalDepth++;
		NewBucket->LocalDepth = SplitBucket->LocalDepth;
		
		for(auto iter = temp.begin(); iter!=temp.end(); ++iter)
		{
			int h = (*iter) & ((1<<GlobalDepth) -1);
			BucketMap[h]->vec.push_back(*iter);
		}
	}
	else
	{
		int idx = SplitIndex & (1<<(SplitBucket->LocalDepth) - 1);

		vector<int>v_idx;
		for (int z = 0; z < (1<<GlobalDepth); ++z)
		{
			int last = z & (1<<(SplitBucket->LocalDepth)) - 1;
			
			if(last==idx)
			{
				v_idx.push_back(z);
			}
		}

		SplitBucket->LocalDepth++;
		NewBucket->LocalDepth = SplitBucket->LocalDepth;
		
		for (int z = v_idx.size()/2; z < v_idx.size(); ++z)
		{
			BucketMap[v_idx[z]] = NewBucket;
		}

		for(auto iter = temp.begin(); iter!=temp.end(); ++iter)
		{
			int h = (*iter) & ((1<<GlobalDepth) -1);
			BucketMap[h]->vec.push_back(*iter);
		}
	}

}


void Merge()
{
	for(int z = 0; z<(1<<(GlobalDepth-1)); z++)
	{
		int h = z & ( ( 1<<((BucketMap[z]->LocalDepth)-1) ) - 1);

		bucket *curr = BucketMap[z];
		bucket *match = BucketMap[ z ^ (1<<(BucketMap[z]->LocalDepth-1)) ];

		if(curr != match)
		{
			int size = curr->vec.size() + match->vec.size();
			if(size <= BucketCapacity)
			{
				copy(match->vec.begin(), match->vec.end(),back_inserter(curr->vec));
				
				vector<int>v;
				for(auto iter = BucketMap.begin(); iter!=BucketMap.end(); ++iter)
				{
					if(iter->second==match)
					{
						v.push_back(iter->first);
					}
				}
				
				delete match;
				
				for(auto j = v.begin(); j!=v.end(); ++j)
				{
					BucketMap[(*j)] = BucketMap[z];
				}
				BucketMap[z]->LocalDepth--;
			}
		}
	}
}


void Shrink()
{
	set<bucket*>Buckets;
	for(auto iter = BucketMap.begin(); iter!=BucketMap.end(); ++iter)
	{
		Buckets.insert(iter->second);
	}

	int cnt = 0;
	int size = Buckets.size();

	for(auto iter =Buckets.begin(); iter!=Buckets.end(); ++iter)
	{
		if ((GlobalDepth - ((*iter)->LocalDepth)) == 1)
			cnt++;
	}

	if(cnt==size)
	{
		GlobalDepth--;
	}
}