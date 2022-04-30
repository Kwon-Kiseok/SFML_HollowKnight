#pragma once

/// <summary>
/// ���ܸ� �������� ���� �Լ��� noexcept�� ����.
/// ��, C++11 ���� �⺻������ ��� �޸� ���� �Լ��� �Ҹ��� �Լ��� �Ϲ������� noexcept�̹Ƿ� ���� ������ �ʿ� ����.
/// 
/// default Ű���带 ���� ��������� ����� �� �⺻ ������, �Ҹ��ڸ� ����ϰڴ� ǥ��
/// 
/// �ǵ����� �ʰ� �ڵ� �ۼ��� �Լ��� delete�� ���� �ǵ������� ������ �� �ִ�.
/// '������ �Լ�'�� public���� �����ϴ� ���� ����.
/// 
/// </summary>
/// <typeparam name="T"></typeparam>

template <typename T>
class Singleton
{
public:
	Singleton(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton& operator=(Singleton&&) = delete;
protected:
	Singleton() noexcept = default;
	virtual ~Singleton() = default;
public:
	static T& GetInstance() noexcept
	{
		static T instance;
		return instance;
	}
};