//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
// $Date:       $2017-02-19
//============================================================================//

/**
 * @file white_box_tests.cpp
 * @author Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
 * 
 * @brief Implementace testu prace s maticemi.
 */


#include <vector>
#include <math.h>
#include "gtest/gtest.h"
#include "white_box_code.h"


namespace WhiteBoxTesting
{

	using namespace ::testing;


	class TestingMatrix : public Test
	{

	protected:

		Matrix matrix;


		Matrix getZero1x1Matrix()
		{
			return Matrix();
		}

		void setZero1x1Matrix()
		{
			matrix = getZero1x1Matrix();
		}


		Matrix get6x6Matrix()
		{
			Matrix matrix = Matrix(6, 6);
			matrix.set(std::vector<std::vector<double>> {
				{1, 4, -2, 2.7, -3.3, 24},
				{5, 3, 0, 21, 212, -22.22},
				{1, -21, 63, 0, 0, 0},
				{-0.001, 212, 31, 9, 6, 1},
				{2, -212, -32, 2, 6, 1},
				{2, 6, 1, 2, 6, -21.2121},
			});

			return matrix;
		}

		void set6x6Matrix()
		{
			matrix = get6x6Matrix();
		}


		Matrix get2x3Matrix()
		{
			Matrix matrix = Matrix(2, 3);
			matrix.set(std::vector<std::vector<double>> {
				{1, 2, 0},
				{0, 1, 0},
			});

			return matrix;
		}

		void set2x3Matrix()
		{
			matrix = get2x3Matrix();
		}


		Matrix get3x2Matrix()
		{
			Matrix matrix = Matrix(3, 2);
			matrix.set(std::vector<std::vector<double>> {
				{0, 1},
				{1, 0},
				{1, 1},
			});

			return matrix;
		}

		void set3x2Matrix()
		{
			matrix = get3x2Matrix();
		}


		Matrix get3x3Matrix()
		{
			Matrix matrix = Matrix(3, 3);
			matrix.set(std::vector<std::vector<double>> {
				{3, 2, 1},
				{2, 1, 2},
				{1, 1, 1},
			});

			return matrix;
		}

		void set3x3Matrix()
		{
			matrix = get3x3Matrix();
		}

	};


	TEST_F(TestingMatrix, Construct)
	{
		EXPECT_NO_THROW(Matrix());
		EXPECT_NO_THROW(Matrix(1, 1));
		EXPECT_NO_THROW(Matrix(12, 23));
		EXPECT_NO_THROW(Matrix(100, 100));
		EXPECT_NO_THROW(Matrix(1231, 3212));

		EXPECT_ANY_THROW(Matrix(0, 0));
		EXPECT_ANY_THROW(Matrix(0, 25));
		EXPECT_ANY_THROW(Matrix(25, 0));
	}


	TEST_F(TestingMatrix, SetValueZero1x1Matrix)
	{
		setZero1x1Matrix();

		EXPECT_FALSE(matrix.set(1, 1, 0));
		EXPECT_FALSE(matrix.set(0, 1, 0));
		EXPECT_FALSE(matrix.set(1, 0, 0));
		EXPECT_FALSE(matrix.set(312, 745, 0));

		EXPECT_TRUE(matrix.set(0, 0, 0));
		EXPECT_TRUE(matrix.set(0, 0, -312));
		EXPECT_TRUE(matrix.set(0, 0, 312));
		EXPECT_TRUE(matrix.set(0, 0, 321312));
		EXPECT_TRUE(matrix.set(0, 0, 321.312));
		EXPECT_TRUE(matrix.set(0, 0, -321.312));
	}


	TEST_F(TestingMatrix, SetValue6x6Matrix)
	{
		set6x6Matrix();

		EXPECT_FALSE(matrix.set(10, 10, 0));
		EXPECT_FALSE(matrix.set(6, 6, 0));
		EXPECT_FALSE(matrix.set(312, 654, 0));

		EXPECT_TRUE(matrix.set(0, 0, 0));
		EXPECT_TRUE(matrix.set(2, 2, -32));
		EXPECT_TRUE(matrix.set(5, 0, -3.2));
		EXPECT_TRUE(matrix.set(2, 4, -3.2));
	}


	TEST_F(TestingMatrix, SetValuesZero1x1Matrix)
	{
		setZero1x1Matrix();

		EXPECT_TRUE(matrix.set(std::vector<std::vector<double>> {{0}}));
		EXPECT_TRUE(matrix.set(std::vector<std::vector<double>> {{321312}}));
		EXPECT_TRUE(matrix.set(std::vector<std::vector<double>> {{-321312}}));
		EXPECT_TRUE(matrix.set(std::vector<std::vector<double>> {{321.312}}));
		EXPECT_TRUE(matrix.set(std::vector<std::vector<double>> {{-321.312}}));
		EXPECT_TRUE(matrix.set(std::vector<std::vector<double>> {
			{-321.312, 12},
			{-321.312, 21},
		}));

		EXPECT_FALSE(matrix.set(std::vector<std::vector<double>> {{}}));
	}


	TEST_F(TestingMatrix, SetValues6x6Matrix)
	{
		set6x6Matrix();
		EXPECT_TRUE(matrix.set(std::vector<std::vector<double>> {
			{1, 4, -2, 2.7, -3.3, 24},
			{5, 3, 0, 21, 212, -22.22},
			{1, -21, 63, 0, 0, 0},
			{-0.001, 212, 31, 9, 6, 1},
			{2, -212, -32, 2, 6, 1},
			{2, 6, 1, 2, 6, -21.2121},
		}));

		EXPECT_FALSE(matrix.set(std::vector<std::vector<double>> {
			{1, 4, -2, 2.7, -3.3, 24},
			{5, 3, 0, 21, 212, -22.22},
			{1, -21, 63, 0, 0},
			{-0.001, 212, 31, 9, 6, 1},
			{2, -212, -32, 2, 6},
		}));
	}


	TEST_F(TestingMatrix, GetValuesZero1x1Matrix)
	{
		setZero1x1Matrix();

		EXPECT_TRUE(isnan(matrix.get(1, 1)));
		EXPECT_TRUE(isnan(matrix.get(10, 10)));
		EXPECT_TRUE(isnan(matrix.get(3212, 433)));

		EXPECT_DOUBLE_EQ(matrix.get(0, 0), 0);
	}


	TEST_F(TestingMatrix, GetValues6x6Matrix)
	{
		set6x6Matrix();

		EXPECT_TRUE(isnan(matrix.get(23, 321)));
		EXPECT_TRUE(isnan(matrix.get(6, 0)));
		EXPECT_TRUE(isnan(matrix.get(3212, 433)));

		EXPECT_DOUBLE_EQ(matrix.get(2, 3), 0);
		EXPECT_DOUBLE_EQ(matrix.get(0, 4), -3.3);
		EXPECT_DOUBLE_EQ(matrix.get(3, 0), -0.001);
	}


	TEST_F(TestingMatrix, Equal)
	{
		Matrix matrixZero1x1 = getZero1x1Matrix();
		Matrix matrix6x6 = get6x6Matrix();
		Matrix matrix2x3 = get2x3Matrix();

		EXPECT_ANY_THROW(matrixZero1x1 == matrix6x6);
		EXPECT_ANY_THROW(matrix6x6 == matrix2x3);

		EXPECT_TRUE(matrix2x3 == matrix2x3);
		EXPECT_TRUE(matrixZero1x1 == matrixZero1x1);

		Matrix new6x6Matrix = matrix6x6;
		new6x6Matrix.set(2, 2, 1);
		EXPECT_FALSE(matrix6x6 == new6x6Matrix);

		Matrix new1x1Matrix = matrixZero1x1;
		new1x1Matrix.set(0, 0, -32);
		EXPECT_FALSE(matrixZero1x1 == new1x1Matrix);
	}


	TEST_F(TestingMatrix, Plus)
	{
		Matrix matrixZero1x1 = getZero1x1Matrix();
		Matrix matrix3x2 = get3x2Matrix();
		Matrix matrix2x3 = get2x3Matrix();

		EXPECT_ANY_THROW(matrixZero1x1 + matrix3x2);
		EXPECT_ANY_THROW(matrix3x2 + matrix2x3);

		Matrix result1 = matrix2x3 + matrix2x3;
		Matrix expected1 = Matrix(2, 3);
		expected1.set(std::vector<std::vector<double>> {
			{2, 4, 0},
			{0, 2, 0},
		});
		EXPECT_TRUE(result1 == expected1);

		Matrix result2 = matrix3x2 + matrix3x2;
		Matrix expected2 = Matrix(3, 2);
		expected2.set(std::vector<std::vector<double>> {
			{0, 2},
			{2, 0},
			{2, 2},
		});
		EXPECT_TRUE(result2 == expected2);
	}


	TEST_F(TestingMatrix, Multiply)
	{
		Matrix matrixZero1x1 = getZero1x1Matrix();
		Matrix matrix3x2 = get3x2Matrix();
		Matrix matrix2x3 = get2x3Matrix();

		EXPECT_ANY_THROW(matrix2x3 * matrixZero1x1);

		Matrix result1 = matrixZero1x1 * matrixZero1x1;
		Matrix expected1 = Matrix();
		EXPECT_TRUE(result1 == expected1);

		Matrix result2 = matrix2x3 * matrix3x2;
		Matrix expected2 = Matrix(2, 2);
		expected2.set(std::vector<std::vector<double>> {
			{2, 1},
			{1, 0},
		});
		EXPECT_TRUE(result2 == expected2);

		Matrix result3 = matrix3x2 * matrix2x3;
		Matrix expected3 = Matrix(3, 3);
		expected3.set(std::vector<std::vector<double>> {
			{0, 1, 0},
			{1, 2, 0},
			{1, 3, 0},
		});
		EXPECT_TRUE(result3 == expected3);
	}


	TEST_F(TestingMatrix, MultiplyConst)
	{
		Matrix matrixZero1x1 = getZero1x1Matrix();
		Matrix matrix6x6 = get6x6Matrix();
		Matrix matrix2x3 = get2x3Matrix();

		Matrix result1 = matrixZero1x1 * 25;
		Matrix expected1 = Matrix();
		EXPECT_TRUE(result1 == expected1);

		Matrix result2 = matrix6x6 * 0;
		Matrix expected2 = Matrix(6, 6);
		EXPECT_TRUE(result2 == expected2);

		Matrix result3 = matrix2x3 * 12;
		Matrix expected3 = Matrix(2, 3);
		expected3.set(std::vector<std::vector<double>> {
			{12, 24, 0},
			{0, 12, 0},
		});
		EXPECT_TRUE(result3 == expected3);
	}


	TEST_F(TestingMatrix, EquationExceptions)
	{
		set3x3Matrix();

		EXPECT_ANY_THROW(matrix.solveEquation(std::vector<double> {}));
		EXPECT_ANY_THROW(matrix.solveEquation(std::vector<double>(2, 0)));

		EXPECT_ANY_THROW(get2x3Matrix().solveEquation(std::vector<double>(2, 0)));
		EXPECT_ANY_THROW(get3x2Matrix().solveEquation(std::vector<double>(3, 0)));

		// singularni matice
		matrix = Matrix(2, 2);
		matrix.set(std::vector<std::vector<double>> {
			{4, 1},
			{12, 3},
		});
		EXPECT_ANY_THROW(matrix.solveEquation(std::vector<double> {5, 15}));
	}


	TEST_F(TestingMatrix, Equation1x1)
	{
		// TODO: pocita spatne, ale melo by fungovat
		setZero1x1Matrix();
		matrix.set(0, 0, 2);

		EXPECT_TRUE(matrix.solveEquation(std::vector<double> {1}) == (std::vector<double> {0.5}));
	}


	TEST_F(TestingMatrix, Equation2x2)
	{
		matrix = Matrix(2, 2);
		matrix.set(std::vector<std::vector<double>> {
			{4, 2},
			{5, -3},
		});

		EXPECT_TRUE(matrix.solveEquation(std::vector<double> {6, 13}) == (std::vector<double> {2, -1}));
	}


	TEST_F(TestingMatrix, Equation3x3)
	{
		set3x3Matrix();
		EXPECT_TRUE(matrix.solveEquation(std::vector<double> {2, 3, 1}) == (std::vector<double> {1, -1, 1}));
	}


	TEST_F(TestingMatrix, Equation6x6)
	{
		set6x6Matrix();
		matrix.set(std::vector<std::vector<double>> {
			{1, 1, -2, 1, 3, -1},
			{2, -1, 1, 2, 1, -3},
			{1, 3, -3, -1, 2, 1},
			{5, 2, -1, -1, 2, 1},
			{-3, -1, 2, 3, 1, 3},
			{4, 3, 1, -6, -3, -2},
		});

		std::vector<double> expected = {1, -2, 3, 4, 2, -1};
		EXPECT_TRUE(matrix.solveEquation(std::vector<double> {4, 20, -15, -3, 16, -27}) == expected);
	}

}

/*** Konec souboru white_box_tests.cpp ***/
