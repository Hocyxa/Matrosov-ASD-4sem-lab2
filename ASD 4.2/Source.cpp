#include <iostream>
#include <vector>

struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};


stats Selection_Sort(std::vector <int> &v)
{
	stats stat;
	size_t max; 
	for (size_t i = 0; i < v.size() - 1; i++)
	{
		max = 0;
		for (size_t j = 0; j < v.size() - i; j++)
		{
			stat.comparison_count ++;
			if (v[max] < v[j])
			{
				max = j;
			}
		}
		if (v[max] != v[v.size() - 1 - i])
		{
			int tmp = v[max];
			v[max] = v[v.size() - 1 - i];
			v[v.size() - 1 - i] = tmp;
			//std::swap(v[max], v[v.size() - 1 - i]);
			stat.copy_count++;
		}
	}
	return stat;
}

stats Sort_Of_Shell(std::vector <int>& v)
{
	stats stat;
	for (size_t d = v.size() / 2; d > 0; d /= 2)
	{
		for (size_t i = d; i < v.size(); ++i)
		{
			stat.comparison_count++;
			for (int j = i - d; j >= 0 && v[j] > v[j + d]; j -= d)
			{
				int tmp = v[j];
				v[j] = v[j + d];
				v[j + d] = tmp;
				//std::swap(v[j], v[j + d]);
				stat.copy_count++;
			}
		}
	}
	return stat;

}



int main()
{
	stats stat;
	
	std::vector<int> v1 = { 8,1,3,10,4,5,2,9,7,6 };
	for (auto i = v1.begin(); i != v1.end(); ++i)
	{
		std::cout << *i << " ";
	}
	std::cout << "\n";
	stat = Selection_Sort(v1);
	for (auto i = v1.begin(); i != v1.end(); ++i)
	{
		std::cout << *i << " ";
	}
	std::cout << "\n";
	std::cout << "Number of comparisons:" << stat.comparison_count << std::endl;
	std::cout << "Number of copies:" << stat.copy_count << std::endl;

	std::cout << std::endl;

	std::vector<int> v2 = { 8,1,3,10,4,5,2,9,7,6 };
	for (auto i = v2.begin(); i != v2.end(); ++i)
	{
		std::cout << *i << " ";
	}
	std::cout << "\n";
	stat = Sort_Of_Shell(v2);
	for (auto i = v2.begin(); i != v2.end(); ++i)
	{
		std::cout << *i << " ";
	}
	std::cout << "\n";
	std::cout << "Number of comparisons:" << stat.comparison_count << std::endl;
	std::cout << "Number of copies:" << stat.copy_count << std::endl;
	

	std::vector<int> v3 = { 8,1,3,10,4,5,2,9,7,6 };
	for (auto i = v3.begin(); i != v3.end(); ++i)
	{
		std::cout << *i << " ";
	}
	std::cout << "\n";
	stat = Heap_Sort(v3);
	for (auto i = v3.begin(); i != v3.end(); ++i)
	{
		std::cout << *i << " ";
	}
	std::cout << "\n";
	std::cout << "Number of comparisons:" << stat.comparison_count << std::endl;
	std::cout << "Number of copies:" << stat.copy_count << std::endl;


	return 0;
}