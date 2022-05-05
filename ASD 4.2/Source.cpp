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

bool sorted(std::vector<int>& data)
{
	for (size_t i = 0; i < data.size()-1; i++)
	{
	
		if (data[i] >= data[i+1]) return false;
	
	}
	return true;
}

std::vector<int> Merge(std::vector<int>& v1, std::vector<int>& v2, size_t size)
{
	std::vector<int> ret (size); //возращаемый массив
	size_t i = 0; //индекс первого массива
	size_t j = 0; // индекс второго массива
	size_t k = 0; //индекс возращаемого массива
	while (k != size)
	{
		if (i == v1.size())
		{
			ret[k] = v2[j];
			j++;
			k++;
			continue;
		}
		if (j == v2.size())
		{
			ret[k] = v1[i];
			i++;
			k++;
			continue;
		}
		if (v1[i] < v2[j])
		{
			ret[k] = v1[i];
			i++;
		}
		else
		{
			ret[k] = v2[j];
			j++;
		}
		k++;
	}
	return ret;
}

stats Two_Way_Merge_Sort(std::vector<int>& data) 
{
	stats stat;
	std::vector<int> tmv(data.size());

	while (1)
	{
		std::vector<int> tmv1(data.size());
		std::vector<int> tmv2(data.size());
		int count = 1; //проверка чётности итерации
		size_t l_old = 0; //пиндекс левой стороны data
		size_t r_old = tmv.size() - 1; //индекс правой стороны data
		size_t l_new = 0; //пиндекс левой стороны tmv
		size_t r_new = tmv.size() - 1; //индекс правой стороны tmv
		while (l_old != r_old)
		{
			size_t left_size = 0;//количество элементов слева
			size_t right_size = 0;//количесвто элементов справа
			tmv1[0] = data[l_old];
			for (size_t i = 0; (data[l_old] <= data[l_old + 1]); l_old++)
			{
				tmv1[i] = data[l_old];
				if (l_old == tmv.size() - 1) return stat; // <---------------------------------------< return
				i++;
				left_size++;
			}
			if (left_size == 0) left_size++;
			tmv2[0] = data[r_old ];
			for (size_t i = 0; data[r_old] <= data[r_old - 1]; r_old--)
			{
				tmv2[i] = data[r_old];
				i++;
				right_size++;
			}
			if (right_size == 0) right_size++;
			std::vector<int> tmv0(left_size + right_size);
			tmv0 = Merge(tmv1, tmv2, left_size + right_size);
			if (count % 2 == 1) //пишем слева
			{
				for (size_t i = 0; i < left_size + right_size; l_new++)
				{
					tmv[l_new] = tmv0[i];
					i++;
				}
				count++;
			}
			if (count % 2 == 0) //пишем справа
			{
				for (size_t i = 0; i < left_size + right_size; r_new--)
				{
					tmv[r_new] = tmv[0];
					i++;
				}
				count++;
			}
		}




		
	}

}

int main()
{
	stats stat;
	/*
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
	*/


	std::vector<int> v3= { 8,1,3,10,4,5,2,9,7,6 };
	for (auto i = v3.begin(); i != v3.end(); ++i)
	{
		std::cout << *i << " ";
	}
	std::cout << "\n";
	stat = Two_Way_Merge_Sort(v3);

	for (auto i = v3.begin(); i != v3.end(); ++i)
	{
		std::cout << *i << " ";
	}
	std::cout << "\n";
	std::cout << "Number of comparisons:" << stat.comparison_count << std::endl;
	std::cout << "Number of copies:" << stat.copy_count << std::endl;


	return 0;
}