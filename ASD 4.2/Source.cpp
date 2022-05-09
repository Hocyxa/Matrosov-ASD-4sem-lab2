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
	
		if (data[i] > data[i+1]) return false;
	
	}
	return true;
}

std::vector<int> Merge(std::vector<int>& v1, std::vector<int>& v2, stats & stat)
{
	std::vector<int> ret (v1.size() + v2.size()); //возращаемый массив
	size_t i = 0; //индекс первого массива
	size_t j = 0; // индекс второго массива
	size_t k = 0; //индекс возращаемого массива
	while (k != v1.size() + v2.size())
	{
		if (i == v1.size())
		{
			ret[k] = v2[j];
			j++;
			k++;
			stat.copy_count++;
			continue;
		}
		if (j == v2.size())
		{
			ret[k] = v1[i];
			i++;
			k++;
			stat.copy_count++;
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
		stat.copy_count++;
		stat.comparison_count++;
		k++;
	}
	return ret;
}

stats Naturial_Two_Way_Merge_Sort(std::vector<int>& data, stats stat)
{
	if (data.size() == 1) return stat;
	if (sorted(data)) return stat;
	std::vector<int> tmv(data.size());
	bool count = true; //проверка чётности итерации
	size_t l_old = 0; //пиндекс левой стороны data
	size_t r_old = data.size() - 1; //индекс правой стороны data
	size_t l_new = 0; //пиндекс левой стороны tmv
	size_t r_new = data.size() - 1; //индекс правой стороны tmv
	while (l_old < r_old)
	{
		std::vector<int> tmv1;
		std::vector<int> tmv2;
		while ((data[l_old] <= data[l_old + 1]) && (l_old < r_old) && (l_old < data.size()))
		{
			tmv1.push_back(data[l_old]);
			l_old++;
			stat.comparison_count++;
		}
		tmv1.push_back(data[l_old]);
		l_old++;
		while ((data[r_old] <= data[r_old - 1]) && (l_old < r_old) && (r_old >= 0))
		{
			tmv2.push_back(data[r_old]);
			r_old--;
			stat.comparison_count++;
		}
		if (l_old <= r_old)
		{
			tmv2.push_back(data[r_old]);
			r_old--;
		}
		std::vector<int> tmv0;
		tmv0 = Merge(tmv1, tmv2, stat);
		if (count)//пишем слева
		{
			for (size_t i = 0; i < tmv0.size(); l_new++)
			{
				tmv[l_new] = tmv0[i];
				i++;
				stat.copy_count++;
			}
			count = false;
		}
		else //пишем справа
		{
			for (size_t i = 0; i < tmv0.size(); r_new--)
			{
				tmv[r_new] = tmv0[i];
				i++;
				stat.copy_count++;
			}
			count = true;
		}
		if (tmv0.size() == data.size())
		{
			data = tmv;
			stat.copy_count += tmv.size();
			return stat;
		}
	}
	if (l_old != data.size())
	{
		stat = Naturial_Two_Way_Merge_Sort(tmv, stat);
	}
	data = tmv;
	stat.copy_count += tmv.size();
	return stat;
}





int main()
{
	stats stat;
	std::vector<int> v1 (10);
	for (auto i = v1.begin(); i != v1.end(); ++i)
	{
		*i = rand() % 10;
	}
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

	std::vector<int> v2 (10);
	for (auto i = v2.begin(); i != v2.end(); ++i)
	{
		*i = rand() % 10;
	}
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
	
	std::cout << std::endl;

	std::vector<int> v3(10);
	for (auto i = v3.begin(); i != v3.end(); ++i)
	{
		*i= rand()%10;
	}
	for (auto i = v3.begin(); i != v3.end(); ++i)
	{
		std::cout << *i << " ";
	}
	std::cout << "\n";
	stats null;
	stat = Naturial_Two_Way_Merge_Sort(v3, null);

	for (auto i = v3.begin(); i != v3.end(); ++i)
	{
		std::cout << *i << " ";
	}
	std::cout << "\n";
	std::cout << "Number of comparisons:" << stat.comparison_count << std::endl;
	std::cout << "Number of copies:" << stat.copy_count << std::endl;


	return 0;
}