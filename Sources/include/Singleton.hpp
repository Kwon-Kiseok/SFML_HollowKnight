#pragma once

/// <summary>
/// 예외를 방출하지 않을 함수는 noexcept로 선언.
/// 단, C++11 에서 기본적으로 모든 메모리 해제 함수와 소멸자 함수는 암묵적으로 noexcept이므로 직접 선언할 필요 없음.
/// 
/// default 키워드를 통해 명시적으로 만들어 둔 기본 생성자, 소멸자를 사용하겠다 표기
/// 
/// 의도되지 않게 자동 작성될 함수를 delete를 통해 의도적으로 삭제할 수 있다.
/// '삭제된 함수'는 public으로 선언하는 것이 관례.
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