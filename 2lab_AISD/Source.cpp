#pragma once
#include <iostream>
template <class T>
class Plenty {
private:
	T* data;
	int size;
	
public:
	Plenty() : data(nullptr), size(0) {}
	Plenty(int size) : data(new T[size]), size(size) {}
	Plenty(Plenty<T>& second) {
		size = second.size;
		data = second.data;
	}
	~Plenty() {
		if (!data)
			delete[] data;
	}

	bool check_num(T num) {
		for (int i = 0; i < size; i++) {
			if (num == data[i])
				return true;
		}
		return false;
	}


	T operator[](const int i) { 
		if (!data)
			throw std::logic_error("arr == nullptr");
		if (i > size - 1 || i < 0)
			throw std::logic_error("invalide index");
		return data[i];
	}

	Plenty& operator+=(T num) 
	{
		if (check_num(num) == false) {
			Plenty tmp(size + 1);
			tmp.size = 0;
			for (int i = 0; i < size; i++) {
				tmp.data[i] = data[i];
				tmp.size++;
			}
			tmp.data[tmp.size] = num;
			data = tmp.data;
			size++;
		}
		return *this;
	}
	Plenty operator+(const Plenty& second) {
		Plenty tmp(size + second.size);
		tmp.size = 0;
		for (int i = 0; i < size; i++) {
			tmp.data[i] = data[i];
			tmp.size++;
		}
		for (int i = 0; i < second.size; i++) {
			if (check_num(second.data[i]) == false)
			{
				tmp.data[tmp.size] = second.data[i];
				tmp.size++;
			}
		}
		return tmp;
	}
	Plenty operator-(const Plenty& second) {
		Plenty tmp(size);
		tmp.size = 0;
		bool flag = false;
		for (int i = 0; i < size; i++) {
			flag = false;
			for (int j = 0; j < second.size; j++) {
				if (data[i] == second.data[j])
				{
					flag = true;
					break;
				}
			}
			if (flag == false)
			{
				tmp.data[tmp.size] = data[i];
				tmp.size++;
			}
		}
		return tmp;
	}
	Plenty operator+(T num) {
		Plenty tmp(size + 1);
		tmp.size = 0;
		if (check_num(num) == false) {
			for (int i = 0; i < size; i++) {
				tmp.data[i] = data[i];
				tmp.size++;
			}
			tmp.data[tmp.size] = num;
			tmp.size++;
		}
		return tmp;
	}
	Plenty operator-(T num)
	{
		Plenty data_n(size);
		for (int i = 0; i < data_n.size; i++) {
			data_n.data[i] = data[i];
		}
		if (check_num(num) == true) {
			for (int i = 0; i < data_n.size; i++) {
				if (data_n.data[i] == num)
				{
					for (int j = i; j < data_n.size - 1; j++) {
						data_n.data[j] = data_n.data[j + 1];
					}
					data_n.size--;
					break;
				}
			}
		}
		else std::cout << "Set have not got this num" << std::endl;
		return data_n;
	}
	Plenty& operator-=(T num) {
		if (check_num(num) == true) {
			for (int i = 0; i < size; i++) {
				if (data[i] == num)
				{
					for (int j = i; j < size - 1; j++) {
						data[j] = data[j + 1];
					}
					size--;
					break;
				}
			}
		}
		else std::cout << "Set have not got this num" << std::endl;
		return *this;
	}
	Plenty intersection(const Plenty& second) {
		Plenty tmp(size);
		tmp.size = 0;
		bool flag = false;
		for (int i = 0; i < size; i++) {
			flag = false;
			for (int j = 0; j < second.size; j++) {
				if (data[i] == second.data[j])
				{
					flag = true;
					break;
				}
			}
			if (flag == true)
			{
				tmp.data[tmp.size] = data[i];
				tmp.size++;
			}
		}
		return tmp;
	}

	bool operator==(const Plenty& second) { 
		if (second.size != size)
			return false;
		else
		{
			bool flag = false;
			for (int i = 0; i < size; i++)
			{
				flag = false;
				for (int j = 0; j < second.size; j++) {
					if (data[i] == second.data[j]) {
						flag = true;
						break;
					}
				}
				if (flag == false)
					return false;
			}
			return true;
		}
	}

	bool operator!=(const Plenty& second) {
		if (second.size != size)
			return true;
		else
		{
			bool flag = true;
			for (int i = 0; i < size; i++)
			{
				flag = true;
				for (int j = 0; j < second.size; j++) {
					if (data[i] == second.data[j]) {
						flag = false;
						break;
					}
				}
				if (flag == true)
					return true;
			}
			return false;
		}
	}
	friend std::ostream& operator<<(std::ostream& s, const Plenty<T>& set)
	{
		for (int i = 0; i < set.size; i++) {
			s << set.data[i] << "  ";
		}
		return s;
	}
};

std::ostream& operator<<(std::ostream& out, const std::pair<int, double>& p)
{
	out << "{" << p.first << ", " << p.second << "}";
	return out;
}

int main() {
	try {
		Plenty<int> p1, p11;
		p1 += 6;
		p1 += 7;
		p1 += 8;
		p1 += 3;
		p1 += 4;
		p11 = p1 + 5;
		p11 = p1 - 6;
		p11 -= 7;
		std::cout << "p 1: " << p1 << std::endl;
		std::cout << "p 11: " << p11 << std::endl;
		std::cout << "p1+p11: " << p1 + p11 << std::endl;
		std::cout << "p1-p11: " << p1 - p11 << std::endl;
		std::cout << "intersection: " << p1.intersection(p11) << std::endl;
		std::cout << "equality: " << (p1 == p11) << std::endl;
		std::cout << "not equality: " << (p1 != p11) << std::endl;
		std::cout << "index: " << p1[1] << std::endl;
		std::cout << std::endl;

		Plenty<float> p2, p22;
		p2 += 6.4;
		p2 += 7.5;
		p2 += 8.9;
		p2 += 1.1;
		p2 += 4.9;
		p22 = p2 + 4.4;
		p22 = p2 - 6.4;
		p22 -= 7.5;
		std::cout << "p 2: " << p2 << std::endl;
		std::cout << "p 22: " << p22 << std::endl;
		std::cout << "p2+p22: " << p2 + p22 << std::endl;
		std::cout << "p2-p22: " << p2 - p22 << std::endl;
		std::cout << "intersection: " << p2.intersection(p22) << std::endl;
		std::cout << "equality: " << (p2 == p22) << std::endl;
		std::cout << "not equality: " << (p2 != p22) << std::endl;
		std::cout << "index: " << p2[1] << std::endl;
		std::cout << std::endl;

		Plenty<std::string> p3, p33;
		p3 += "mom";
		p3 += "nik";
		p3 += "kot";
		p3 += "nen";
		p3 += "pol";
		p33 = p3 + "ret";
		p33 = p3 - "mom";
		p33 -= "nik";
		p33 += "you";
		std::cout << "p 3: " << p3 << std::endl;
		std::cout << "p 33: " << p33 << std::endl;
		std::cout << "p3+p33: " << p3 + p33 << std::endl;
		std::cout << "p3-p33: " << p3 - p33 << std::endl;
		std::cout << "intersection: " << p3.intersection(p33) << std::endl;
		std::cout << "equality: " << (p3 == p33) << std::endl;
		std::cout << "not equality: " << (p3 != p33) << std::endl;
		std::cout << "index: " << p3[1] << std::endl;
		std::cout << std::endl;

		Plenty<std::pair<int, double>> p4, p44;
		p4 += {1, 3.2};
		p4 += {2, 5.7};
		p4 += {3, 4.4};
		p4 += {8, 9.0};
		p4 += {10, 3.5};
		p44 = p4 + std::pair<int, double>(1, 4.4);
		p44 = p4 - std::pair<int, double>(1, 3.2);
		p44 -= {2, 5.7};
		std::cout << "p 4: " << p4 << std::endl;
		std::cout << "p 44: " << p44 << std::endl;
		std::cout << "p4+p44: " << p4 + p44 << std::endl;
		std::cout << "p4-p44: " << p4 - p44 << std::endl;
		std::cout << "intersection: " << p4.intersection(p44) << std::endl;
		std::cout << "equality: " << (p4 == p44) << std::endl;
		std::cout << "not equality: " << (p4 != p44) << std::endl;
		std::cout << "index: " << p4[1] << std::endl;
		std::cout << std::endl;

		
		Plenty<std::pair<int, double>> p, pp;
		p += {1, 3.2};
		p += {2, 5.7};
		p += {3, 4.4};
		pp = p + std::pair<int, double>(1, 4.4);
		p += {1, 4.4};
		std::cout << "p: " << p << std::endl;
		std::cout << "pp: " << pp << std::endl;
		std::cout << "equality: " << (p == pp) << std::endl;
		std::cout << "not equality: " << (p != pp) << std::endl;
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

}