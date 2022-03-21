#pragma once

//
//�׳�����
// https://mp.weixin.qq.com/s/0qjOX8kxEspjBwjTv-aBpA
// �����C++���ű��1�˵�20
//

#include <iostream>

//
//٤����
// f(x+1) = x*f(x)
// f(n) = (n-1)!
//
#include <cmath>
void maths_func()
{
	auto ret = std::tgamma(20 + 1);
	std::cout << "maths_func ret: " << ret << std::endl;
}

//
//��������
// make_index_sequence
// ����һ��0,1,2...n-1������
//
#include <xutility>
template<std::size_t...I>
constexpr auto foo(std::index_sequence<I...>)
{
	return ((I + 1) * ...);
}
void lang_func()
{
	auto ret = foo(std::make_index_sequence<20>());
	std::cout << "lang_func ret: " << ret << std::endl;
}

//
//��ͨ�汾
// ���ݿ�����/�ֶ�������
//
#include <stdio.h>
void normal_func()
{
	int i;
	long long ret;
	for (i = 1, ret = 1; i <= 20; ret *= i++)
		;
	std::cout << "normal_func ret: " << ret << std::endl;

	//yyds
	printf("%lld", (long long)1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 * 15 * 16 * 17 * 18 * 19 * 20);
}

//
//�������
// �üһ�
//
#include <string>
#include <memory>

struct IBaseInterface {
	virtual ~IBaseInterface() = 0;
};
inline IBaseInterface::~IBaseInterface() = default;

struct IDataProvider : virtual public IBaseInterface {
	virtual int first() = 0;
	virtual int last() = 0;
	virtual int next(int v) = 0;
};

struct ICalculator : virtual public IBaseInterface {
	virtual long long calc(IDataProvider*) = 0;
};

struct IPrinter : virtual public IBaseInterface {
	virtual void print(const std::string&) = 0;
};

struct ISerializer : virtual public IBaseInterface {
	virtual std::string serialize(long long value) = 0;
};

struct IRunnable : virtual public IBaseInterface {
	virtual void run() = 0;
};

class Foo : virtual public IRunnable {
	std::shared_ptr<IDataProvider> m_dp;
	std::shared_ptr<ICalculator> m_c;
	std::shared_ptr<ISerializer> m_s;
	std::shared_ptr<IPrinter> m_p;
public:
	Foo(std::shared_ptr<IDataProvider> dp, std::shared_ptr<ICalculator> c, std::shared_ptr<ISerializer> s, std::shared_ptr<IPrinter> p) : m_dp(std::move(dp)), m_c(std::move(c)), m_s(std::move(s)), m_p(std::move(p)) {}
	void run() override { return  m_p->print(m_s->serialize(m_c->calc(m_dp.get()))); }
};

class DefaultSerializer : virtual public ISerializer {
public:
	std::string serialize(long long value) override { return std::to_string(value); }
};

class StreamPrinter : virtual public IPrinter {
	std::ostream& m_os;
public:
	explicit StreamPrinter(std::ostream& os) : m_os(os) {}
	void print(const std::string& s)  override { m_os << s << std::endl; }
};

class MultiplyAccumulateCalculator : virtual public ICalculator {
public:
	long long calc(IDataProvider* dp) override {
		int i = dp->first();
		long long j = i;
		do
			j *= (i = dp->next(i));
		while (i != dp->last());
		return j;
	}
};

void oop_func()
{
	struct MyDataProvider : virtual public IDataProvider {
		int first() override { return 1; }
		int last() override { return 20; }
		int next(int v) override { return v + 1; }
	};
	Foo foo(std::make_shared<MyDataProvider>(), std::make_shared<MultiplyAccumulateCalculator>(), std::make_shared<DefaultSerializer>(), std::make_shared<StreamPrinter>(std::cout));
	foo.run();
}

//
//�����Ż�
// __m128 ӳ�䵽 XMM [0-7] �Ĵ���
// ��16�ֽڱ߽����Զ�����
// ARM �������ϲ�֧�ָ���������
// Microsoft ר��
// 
// SSEָ��ʹ��xmm0��xmm8���ݴ���
// _mm_xxx_psΪ���ֲ�������
// 
#include <xmmintrin.h>

double foo(int x) {
	__m128 a = { 1.0f, 2.0f, 3.0f, 4.0f };
	__m128 b = { 4.0f, 4.0f, 4.0f, 4.0f };
	__m128 c = { 1.0f, 1.0f, 1.0f, 1.0f };
	for (int i = 0; i < x / 4; ++i, a = _mm_add_ps(a, b))
		c = _mm_mul_ps(c, a);
	for (int i = x % 4; i < 4; ++i)
		a.m128_f32[i] = 1.0f;
	c = _mm_mul_ps(c, a);
	return (double)c.m128_f32[0] * (double)c.m128_f32[1] * (double)c.m128_f32[2] * (double)c.m128_f32[3];
}

void parallel_func()
{
	auto ret = foo(20);
	std::cout << "parallel_func ret: " << ret << std::endl;
}

//
//ħ��
//
#include <numeric>
#include <vector>
#include <functional>
void magic_func()
{
	std::vector<int> v(std::atoi(std::end(__DATE__) - (__LINE__) / 2) - 1); // 2021�꣬�����У����ﲻ����
	std::iota(v.begin(), v.end(), 1);
	std::cout << std::accumulate(v.begin(), v.end(), 1ull, std::multiplies<>()) << std::endl;
}

//
//���꺢����
//

/*

#include <boost/preprocessor.hpp>

// ����boost.preprocessor���ṩ255���µ���������
// ����ʹ��sequence�� (ʮλ��λ)(ǧλ��λ)(ʮ��λ��λ) �ķ�ʽ����ʾ��������

// ����λ�ӷ���(77)(66)(55) + (44)(33)(22) = (121)(99)(77)
#define PP_ADD_N_N_CARRY_OP(R, DATA, I, ELEM) (BOOST_PP_ADD(BOOST_PP_SEQ_ELEM(I, DATA), ELEM))
#define PP_ADD_N_N_CARRY(SEQ_A, SEQ_B) BOOST_PP_SEQ_FOR_EACH_I(PP_ADD_N_N_CARRY_OP, SEQ_A, SEQ_B)

// ��λ�ӷ���(121)(99)(77) = ��21)(0)(78)
// ע��SEQ_A�ĳ���Ҫ��SEQ_B��
#define PP_ADD_N_N_OP(S, STATE, ELEM_CARRY) \
	BOOST_PP_SEQ_PUSH_FRONT( \
			BOOST_PP_SEQ_REPLACE(STATE, 0, BOOST_PP_MOD(BOOST_PP_ADD(BOOST_PP_SEQ_HEAD(STATE), ELEM_CARRY), 100)), \
			BOOST_PP_DIV(BOOST_PP_ADD(BOOST_PP_SEQ_HEAD(STATE), ELEM_CARRY), 100) \
			)
#define PP_ADD_N_N(SEQ_A, SEQ_B) BOOST_PP_SEQ_REVERSE(BOOST_PP_SEQ_FOLD_LEFT(PP_ADD_N_N_OP, BOOST_PP_SEQ_NIL(0), PP_ADD_N_N_CARRY(SEQ_A, SEQ_B)))

// ûʲô��˵�ģ�X*N = X+X+X+X+X+...+X
#define PP_MUL_N_1_EXP_OP(Z, I, DATA) (DATA)
#define PP_MUL_N_1_EXP(SEQ_N, N) BOOST_PP_REPEAT(N, PP_MUL_N_1_EXP_OP, SEQ_N)
#define PP_MUL_N_1_MYOP(S, STATE, ITEM) PP_ADD_N_N(STATE, ITEM)
#define PP_MUL_N_1_FWD(EXP) BOOST_PP_SEQ_FOLD_LEFT(PP_MUL_N_1_MYOP, BOOST_PP_SEQ_HEAD(EXP), BOOST_PP_SEQ_TAIL(EXP))
#define PP_MUL_N_1(SEQ_N, N) PP_MUL_N_1_FWD(PP_MUL_N_1_EXP(SEQ_N, N))

#define FACT5 PP_MUL_N_1(PP_MUL_N_1(PP_MUL_N_1(PP_MUL_N_1((1), 2), 3), 4), 5)
#define FACT10 PP_MUL_N_1(PP_MUL_N_1(PP_MUL_N_1(PP_MUL_N_1(PP_MUL_N_1(FACT5, 6), 7), 8), 9), 10)
#define FACT15 PP_MUL_N_1(PP_MUL_N_1(PP_MUL_N_1(PP_MUL_N_1(PP_MUL_N_1(FACT10, 11), 12), 13), 14), 15)
#define FACT20 PP_MUL_N_1(PP_MUL_N_1(PP_MUL_N_1(PP_MUL_N_1(PP_MUL_N_1(FACT15, 16), 17), 18), 19), 20)
#define FACT25 PP_MUL_N_1(PP_MUL_N_1(PP_MUL_N_1(PP_MUL_N_1(PP_MUL_N_1(FACT20, 21), 22), 23), 24), 25)

static_assert(false, BOOST_PP_STRINGIZE(FACT10));

*/

//
//ģ��Ԫ
// ������
//

#include <iomanip>
#include <type_traits>

using BaseType_t = long long;
constexpr BaseType_t lgBase = 9; // ע��10000*10000�ոպ�С��int��ȡֵ��Χ
constexpr BaseType_t Base = 1000000000; // ע��10000*10000�ոպ�С��int��ȡֵ��Χ

// �������ı�ʾ
template<BaseType_t...I> struct BigInteger {
	using type = BigInteger;
};

// ����
template<class T1, class T2> struct BI_Cat;
template<BaseType_t...I1, BaseType_t...I2> struct BI_Cat <BigInteger<I1...>, BigInteger<I2...>> : BigInteger<I1..., I2...> {};

// ����һ����Ԫ����*Base��
template<class T> struct BI_SHL;
template<BaseType_t...I> struct BI_SHL<BigInteger<I...>> : BigInteger<I..., 0> {};

// ȥ����ͷ��0
template<class T> struct BI_Remove_Zeros : T {};
template<BaseType_t...I> struct BI_Remove_Zeros<BigInteger<0, I...>> : BI_Remove_Zeros<BigInteger<I...>> {};

// ���0��N����Ԫ
template<int X, class IS> struct BI_Fill_Impl;
template<int X, class T, T...I> struct BI_Fill_Impl<X, std::integer_sequence<T, I...>> : BigInteger<(I, X)...> {};
template<int Size> struct BI_Fill_Zeros : BI_Fill_Impl<0, std::make_index_sequence<Size>> {};

template<class T, int N> struct BI_Resize;
template<BaseType_t...I, int N> struct BI_Resize<BigInteger<I...>, N> : BI_Cat<typename BI_Fill_Zeros<N - sizeof...(I)>::type, BigInteger<I...>> {};

// ���ؽϴ����ֵ
template<int A, int B> struct int_min : std::integral_constant<int, (A < B ? B : A)> {};

// �ǽ�λ�ӷ����Ȱ���������λ���ĳ�һ����Ȼ���������
template<class A, class B, class ShouldResize> struct BI_AddNotCarry_Impl;
template<BaseType_t...I1, BaseType_t...I2> struct BI_AddNotCarry_Impl <BigInteger<I1...>, BigInteger<I2...>, std::true_type> : BigInteger<(I1 + I2)...> {};

template<BaseType_t...I1, BaseType_t...I2> struct BI_AddNotCarry_Impl <BigInteger<I1...>, BigInteger<I2...>, std::false_type> :BI_AddNotCarry_Impl<typename BI_Resize<BigInteger<I1...>, int_min<sizeof...(I1), sizeof...(I2)>::value>::type, typename BI_Resize<BigInteger<I2...>, int_min<sizeof...(I1), sizeof...(I2)>::value>::type, std::true_type> {};

template<class A, class B> struct BI_AddNotCarry;
template<BaseType_t...I1, BaseType_t...I2> struct BI_AddNotCarry <BigInteger<I1...>, BigInteger<I2...>> :BI_AddNotCarry_Impl<BigInteger<I1...>, BigInteger<I2...>, std::bool_constant<sizeof...(I1) == sizeof...(I2)>> {};

// �ж��Ƿ�Ϊ0
template<class Y> struct BI_IsZero;
template<BaseType_t...I> struct BI_IsZero<BigInteger<I...>> : std::bool_constant<((I == 0) && ...)> {};

// �Զ���λ
template<class A> struct BI_Carry;
template<class A, class B> struct BI_Add : BI_Carry<typename BI_AddNotCarry<A, B>::type> {};

template<class Mod, class Div, class ShouldCalc = typename BI_IsZero<Div>::type> struct BI_Carry_Impl;
template<class Mod, class Div> struct BI_Carry_Impl<Mod, Div, std::true_type> :Mod {};
template<class Mod, class Div> struct BI_Carry_Impl<Mod, Div, std::false_type> :BI_Add<Mod, typename BI_SHL<Div>::type > {};
template<BaseType_t...I> struct BI_Carry<BigInteger<I...>> :BI_Remove_Zeros<typename BI_Carry_Impl<BigInteger<(I% Base)...>, BigInteger<(I / Base)...>>::type> {};

// ����X���Զ���λ
template<class A, int X> struct BI_MulX;
template<BaseType_t...I1, int X> struct BI_MulX <BigInteger<I1...>, X> :BI_Carry<BigInteger<(I1* X)...>> {};

// ����׳�
template<int X> struct BI_Fact : BI_MulX<typename BI_Fact<X - 1>::type, X> {};
template<> struct BI_Fact<0> : BigInteger<1> {};

template<BaseType_t...I>
std::ostream& operator<<(std::ostream & out, BigInteger<I...>) {
	return ((out << std::setfill('0') << I << std::setw(lgBase)), ...);
}

void guigui_func()
{
	std::cout << typename BI_Fact<20>::type() << std::endl;
}