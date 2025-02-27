#pragma once
#include <windows.h>
#include <iostream>
#include <sql.h>
#include <sqlext.h>
#include <odbcinst.h>
#include <codecvt>
#include <locale>
#include <string>

using namespace std;

class Sctructure {
public:
    SQLLEN indicator;

    SQLHENV henv;
    SQLHDBC hdbc;
    SQLRETURN retcode;
    SQLWCHAR addSql[100];
    SQLWCHAR delSql[100];
    SQLWCHAR updateSql[100];
    SQLWCHAR viewSql[100];
    SQLCHAR colData[1024];
    SQLWCHAR query[1024];
    SQLWCHAR searchSql[100];
    SQLWCHAR queryEnter[100];

    Sctructure() {
        henv = SQL_NULL_HANDLE;
        hdbc = SQL_NULL_HANDLE;
    }

    Sctructure(wstring uid, wstring pwd, wstring dsn) {
        retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error start." << std::endl;
        }

        retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error version ODBC." << std::endl;
        }

        retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error connection." << std::endl;
        }

        std::wstring connStr = L"DSN=" + dsn + L";UID=" + uid + L";PWD=" + pwd;

        SQLWCHAR* wideConnStr = const_cast<SQLWCHAR*>(connStr.c_str());

        SQLWCHAR connStrOut[1024];
        SQLSMALLINT connStrOutLen;
        retcode = SQLDriverConnectW(hdbc, NULL, wideConnStr, SQL_NTS, connStrOut, sizeof(connStrOut), &connStrOutLen, SQL_DRIVER_COMPLETE);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error connection to the database." << std::endl;
        }
    }

    ~Sctructure() {
        SQLDisconnect(hdbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
        SQLFreeHandle(SQL_HANDLE_ENV, henv);
    }

    void init(wstring uid_class) {
        SQLHSTMT hstmt1;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt1);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 1." << std::endl;
        }

        SQLWCHAR queryRating[] = L"SELECT * FROM rating";
        retcode = SQLExecDirectW(hstmt1, queryRating, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 1." << std::endl;
            SQLWCHAR queryRatingCreate[] = L"CREATE TABLE rating (r_id int PRIMARY KEY, r_year_ int, r_class_id int, r_subject_id int, r_point_quarter int, r_point_part_year int, r_point_year int, r_point_exam int, r_point_end int)";
            retcode = SQLExecDirectW(hstmt1, queryRatingCreate, SQL_NTS);
            if (retcode != SQL_SUCCESS) {
                std::cerr << "Error SQL check 2." << std::endl;
            }
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt1);

        SQLHSTMT hstmt2;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt2);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 2." << std::endl;
        }

        SQLWCHAR queryParants[] = L"SELECT * FROM parants";
        retcode = SQLExecDirectW(hstmt1, queryParants, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 3." << std::endl;
            SQLWCHAR queryParantsCreate[] = L"CREATE TABLE parants (p_id int PRIMARY KEY, p_surname varchar, p_first_name varchar, p_surname_2 varchar, p_address_id int, p_status varchar)";
            retcode = SQLExecDirectW(hstmt1, queryParantsCreate, SQL_NTS);
            if (retcode != SQL_SUCCESS) {
                std::cerr << "Error SQL check 4." << std::endl;
            }
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt2);

        SQLHSTMT hstmt3;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt3);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 3." << std::endl;
        }

        SQLWCHAR querySchool[] = L"SELECT * FROM schoolboy";
        retcode = SQLExecDirectW(hstmt3, querySchool, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 5." << std::endl;
            SQLWCHAR querySchoolCreate[] = L"CREATE TABLE schoolboy (s_id int PRIMARY KEY, s_p_id int, s_r_id int, s_surname varchar, s_first_name varchar, s_surname_2 varchar, s_address_id int, s_birth_date int, s_class_id int, s_adm_year int)";
            retcode = SQLExecDirectW(hstmt3, querySchoolCreate, SQL_NTS);
            if (retcode != SQL_SUCCESS) {
                std::cerr << "Error SQL check 6." << std::endl;
            }
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt3);

        SQLHSTMT hstmt24;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt24);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 19." << std::endl;
        }

        SQLWCHAR queryClass[] = L"SELECT * FROM class_";
        retcode = SQLExecDirectW(hstmt24, queryClass, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 5." << std::endl;
            SQLWCHAR queryClassCreate[] = L"CREATE TABLE class_ (cl_id int PRIMARY KEY, cl_name int)";
            retcode = SQLExecDirectW(hstmt24, queryClassCreate, SQL_NTS);
            if (retcode != SQL_SUCCESS) {
                std::cerr << "Error SQL check 20." << std::endl;
            }
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt24);

        SQLHSTMT hstmt25;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt25);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 21." << std::endl;
        }

        SQLWCHAR queryAddress[] = L"SELECT * FROM address";
        retcode = SQLExecDirectW(hstmt25, queryAddress, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 5." << std::endl;
            SQLWCHAR queryAddressCreate[] = L"CREATE TABLE address (ad_id int PRIMARY KEY, ad_name varchar)";
            retcode = SQLExecDirectW(hstmt24, queryAddressCreate, SQL_NTS);
            if (retcode != SQL_SUCCESS) {
                std::cerr << "Error SQL check 22." << std::endl;
            }
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt25);

        SQLHSTMT hstmt26;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt26);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 23." << std::endl;
        }

        SQLWCHAR querySubject[] = L"SELECT * FROM subject";
        retcode = SQLExecDirectW(hstmt26, querySubject, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 5." << std::endl;
            SQLWCHAR querySubjectCreate[] = L"CREATE TABLE subject (su_id int PRIMARY KEY, su_name varchar)";
            retcode = SQLExecDirectW(hstmt26, querySubjectCreate, SQL_NTS);
            if (retcode != SQL_SUCCESS) {
                std::cerr << "Error SQL check 24." << std::endl;
            }
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt26);

        SQLHSTMT hstmt31;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt31);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 25." << std::endl;
        }

        swprintf(queryEnter, sizeof(queryEnter) / sizeof(queryEnter[0]),
            L"SELECT enter_db('%ls')",
            uid_class.c_str());

        retcode = SQLExecDirectW(hstmt31, queryEnter, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 25." << std::endl;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt31);
    }

    void exit(wstring uid_class) {
        SQLHSTMT hstmt31;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt31);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 25." << std::endl;
        }

        swprintf(queryEnter, sizeof(queryEnter) / sizeof(queryEnter[0]),
            L"SELECT exit_db('%ls')",
            uid_class.c_str());

        retcode = SQLExecDirectW(hstmt31, queryEnter, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 25." << std::endl;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt31);
    }

    void menu() {
        cout << "1. Writing an element." << endl;
        cout << "2. Deleting an item." << endl;
        cout << "3. Editing an entry by number." << endl;
        cout << "4. Search by field." << endl;
        cout << "5. Viewing the table." << endl;
        cout << "6. Search by field(ALL)." << endl;
        cout << "7. Update by id/column." << endl;
        cout << "8. DB Structure (ROOT)." << endl;
        cout << "0. Exit." << endl;
    }

    void structure() {
        printf("\033c");
        menu();
        SQLHSTMT hstmt_test1;
        wcscpy_s(query, 1024, L"\d");

        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt_test1);

        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check." << std::endl;
        }

        retcode = SQLExecDirectW(hstmt_test1, query, SQL_NTS);

        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error executing SQL query." << std::endl;
        }
        cout << "| schema |" << " name |" << " type |" << " owner |" << endl;
        cout << "--------------------------------" << endl;
        while (SQLFetch(hstmt_test1) == SQL_SUCCESS) {
            SQLGetData(hstmt_test1, 1, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L"| %s /", colData);

            SQLGetData(hstmt_test1, 2, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s /", colData);

            SQLGetData(hstmt_test1, 3, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s /", colData);

            SQLGetData(hstmt_test1, 4, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s |\n", colData);
        }

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt_test1);
        int exit;
        cout << endl;
        cout << "Write rand-number";
        cin >> exit;
    }

    void all_find() {
        printf("\033c");
        menu();
        wstring findText = L"NULL";
        SQLHSTMT hstmt_test1;

        cout << "Write text: ";
        wcin >> findText;

        swprintf(searchSql, sizeof(searchSql) / sizeof(searchSql[0]),
            L"SELECT*FROM search_columns('%ls', '{parants, rating, schoolboy, address, class, subject, history}')",
            findText.c_str());

        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt_test1);

        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check." << std::endl;
        }

        retcode = SQLExecDirectW(hstmt_test1, searchSql, SQL_NTS);

        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error executing SQL query." << std::endl;
        }

        cout << "| schema_name |" << " table_name |" << " column_name |" << " row_ctid |" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        while (SQLFetch(hstmt_test1) == SQL_SUCCESS) {
            SQLGetData(hstmt_test1, 1, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L"| %s /", colData);

            SQLGetData(hstmt_test1, 2, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s /", colData);

            SQLGetData(hstmt_test1, 3, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s /", colData);

            SQLGetData(hstmt_test1, 4, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s |\n", colData);
        }

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt_test1);
        int exit;
        cout << endl;
        cout << "Write rand-number";
        cin >> exit;
    }

    void print() {
        printf("\033c");
        menu();
        SQLHSTMT hstmt_test1;
        wcscpy_s(query, 1024, L"SELECT * FROM history");

        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt_test1);

        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check." << std::endl;
        }

        retcode = SQLExecDirectW(hstmt_test1, query, SQL_NTS);

        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error executing SQL query." << std::endl;
        }
        cout << "| id |" << " _action |" << " _user |" << " _time |" << endl;
        cout << "--------------------------------" << endl;
        while (SQLFetch(hstmt_test1) == SQL_SUCCESS) {
            SQLGetData(hstmt_test1, 1, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L"| %s /", colData);

            SQLGetData(hstmt_test1, 2, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s /", colData);

            SQLGetData(hstmt_test1, 3, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s /", colData);

            SQLGetData(hstmt_test1, 4, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s |\n", colData);
        }

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt_test1);
        int exit;
        cout << endl;
        cout << "Write rand-number";
        cin >> exit;
    }
};

class Parants : Sctructure {
public:
    using Sctructure::Sctructure;

    int p_id = 0;
    int p_address_id = 0;

    wstring p_surname = L"NULL";
    wstring p_first_name = L"NULL";
    wstring p_surname_2 = L"NULL";
    wstring p_status = L"NULL";
    wstring findText = L"NULL";

    void add(wstring uid) {
                printf("\033c");
                menu();
                SQLHSTMT hstmt5;
                retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt5);
                if (retcode != SQL_SUCCESS) {
                    std::cerr << "Error operation check 5." << std::endl;
                }
                cout << "| 'da' | 'da' | 'da' | 1 | 'da' | " << endl;
                cout << "Write surname: ";
                wcin >> p_surname;
                cout << "Write first_name: ";
                wcin >> p_first_name;
                cout << "Write surname_2: ";
                wcin >> p_surname_2;
                cout << "Write address_id: ";
                wcin >> p_address_id;
                cout << "Write status: ";
                wcin >> p_status;

                swprintf(addSql, sizeof(addSql) / sizeof(addSql[0]),
                                L"SELECT add_parant('%ls', '%ls','%ls', %d, '%ls', '%ls')",
                                p_surname.c_str(), p_first_name.c_str(), p_surname_2.c_str(), p_address_id, p_status.c_str(), uid.c_str());

                retcode = SQLExecDirectW(hstmt5, addSql, SQL_NTS);
                if (retcode != SQL_SUCCESS) {
                    std::cerr << "Error SQL check 7." << std::endl;
                }
                SQLFreeHandle(SQL_HANDLE_STMT, hstmt5);
    }

    void remove(wstring uid) {
                printf("\033c");
                menu();

                SQLHSTMT hstmt7;
                retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt7);
                if (retcode != SQL_SUCCESS) {
                    std::cerr << "Error operation check 7." << std::endl;
                }
                p_id = 0;
                cout << "Write Id: ";
                wcin >> p_id;

                swprintf(delSql, sizeof(delSql) / sizeof(delSql[0]), 
                    L"SELECT del_parant(%d, '%ls')", 
                    p_id, uid.c_str());

                retcode = SQLExecDirectW(hstmt7, delSql, SQL_NTS);
                if (retcode != SQL_SUCCESS) {
                    std::cerr << "Error SQL check 9." << std::endl;
                }
                SQLFreeHandle(SQL_HANDLE_STMT, hstmt7);
    }

    void update(wstring uid) {
                printf("\033c");
                menu();

                SQLHSTMT hstmt10;
                retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt10);
                if (retcode != SQL_SUCCESS) {
                    std::cerr << "Error operation check 10." << std::endl;
                }
                 
                cout << "| 1 | 'da' | 'da' | 'da' | 1 | 'da' | " << endl;
                cout << "Write id: ";
                wcin >> p_id;
                cout << "Write surname: ";
                wcin >> p_surname;
                cout << "Write fisrt_name: ";
                wcin >> p_first_name;
                cout << "Write surname_2: ";
                wcin >> p_surname_2;
                cout << "Write address_id: ";
                wcin >> p_address_id;
                cout << "Write status: ";
                wcin >> p_status;

                swprintf(updateSql, sizeof(updateSql) / sizeof(updateSql[0]),
                    L"SELECT update_parant(%d,'%ls', '%ls','%ls', %d, '%ls', '%ls')",
                    p_id, p_surname.c_str(), p_first_name.c_str(), p_surname_2.c_str(), p_address_id, p_status.c_str(), uid.c_str());

                retcode = SQLExecDirectW(hstmt10, updateSql, SQL_NTS);
                if (retcode != SQL_SUCCESS) {
                    std::cerr << "Error SQL check 11." << std::endl;
                }
                SQLFreeHandle(SQL_HANDLE_STMT, hstmt10);
    }

    void updateByValue(int id, wstring first, wstring uid) {
        printf("\033c");
        menu();

        SQLHSTMT hstmt10;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt10);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 10." << std::endl;
        }
        p_id = id;
        wstring str;
        int inter;

        if (first == L"p_surname" || first == L"p_first_name" || first == L"p_surname_2") {
            cout << "Write second value: ";
            wcin >> str;
            swprintf(updateSql, sizeof(updateSql) / sizeof(updateSql[0]),
                L"select upd_val_par_std('%d','%ls','%ls','%ls')",
                p_id, first.c_str(), str.c_str(), uid.c_str());
        }

        if (first == L"p_address_id") {
            cout << "Write second value: ";
            wcin >> inter;
            swprintf(updateSql, sizeof(updateSql) / sizeof(updateSql[0]),
                L"select upd_val_par_int('%d','%ls',%d,'%ls')",
                p_id, first.c_str(), inter, uid.c_str());
        }

        retcode = SQLExecDirectW(hstmt10, updateSql, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 11." << std::endl;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt10);
    }

    void find() {
                printf("\033c");
                menu();

                SQLHSTMT hstmt_test1;

                cout << "Write text: ";
                wcin >> findText;

                swprintf(searchSql, sizeof(searchSql) / sizeof(searchSql[0]),
                    L"SELECT*FROM search_columns('%ls', '{parants}')",
                    findText.c_str());

                retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt_test1);

                if (retcode != SQL_SUCCESS) {
                    std::cerr << "Error operation check." << std::endl;
                }

                retcode = SQLExecDirectW(hstmt_test1, searchSql, SQL_NTS);

                if (retcode != SQL_SUCCESS) {
                    std::cerr << "Error executing SQL query." << std::endl;
                }

                cout << "| schema_name |" << " table_name |" << " column_name |" << " row_ctid |"  << endl;
                cout << "------------------------------------------------------------------------" << endl;
                while (SQLFetch(hstmt_test1) == SQL_SUCCESS) {
                    SQLGetData(hstmt_test1, 1, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
                    wprintf(L"| %s /", colData);

                    SQLGetData(hstmt_test1, 2, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
                    wprintf(L" %s /", colData);

                    SQLGetData(hstmt_test1, 3, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
                    wprintf(L" %s /", colData);

                    SQLGetData(hstmt_test1, 4, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
                    wprintf(L" %s |\n", colData);
                }

                SQLFreeHandle(SQL_HANDLE_STMT, hstmt_test1);
                int exit;
                cout << endl;
                cout << "Write rand-number";
                cin >> exit;
    }

    void print() {
                printf("\033c");
                menu();
                SQLHSTMT hstmt_test1;
                wcscpy_s(query, 1024, L"SELECT * FROM parants ORDER BY p_id");

                retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt_test1);

                if (retcode != SQL_SUCCESS) {
                    std::cerr << "Error operation check." << std::endl;
                }

                retcode = SQLExecDirectW(hstmt_test1, query, SQL_NTS);

                if (retcode != SQL_SUCCESS) {
                    std::cerr << "Error executing SQL query." << std::endl;
                }

                cout << "| p_id |" << " p_surname |" << " p_first_name |" << " p_surname_2 |" << " p_address |" << " p_status |" << endl;
                cout << "------------------------------------------------------------------------" << endl;
                while (SQLFetch(hstmt_test1) == SQL_SUCCESS) {
                    SQLGetData(hstmt_test1, 1, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
                    wprintf(L"| %s /", colData);

                    SQLGetData(hstmt_test1, 2, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
                    wprintf(L" %s /", colData);

                    SQLGetData(hstmt_test1, 3, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
                    wprintf(L" %s /", colData);

                    SQLGetData(hstmt_test1, 4, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
                    wprintf(L" %s /", colData);

                    SQLGetData(hstmt_test1, 5, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
                    wprintf(L" %s /", colData);

                    SQLGetData(hstmt_test1, 6, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
                    wprintf(L" %s |\n", colData);
                }

                SQLFreeHandle(SQL_HANDLE_STMT, hstmt_test1);
                int exit;
                cout << endl;
                cout << "Write rand-number";
                cin >> exit;
    }
};

class Schoolboy : Sctructure {
public:
    using Sctructure::Sctructure;

    int s_id = 0;
    int s_p_id = 0;
    int s_r_id = 0;
    int s_address_id = 0;
    int s_birth_date = 0;
    int s_class_id = 0;
    int s_adm_year = 0;

    wstring s_surname = L"NULL";
    wstring s_first_name = L"NULL";
    wstring s_surname_2 = L"NULL";
    wstring findText = L"NULL";

    void add(wstring uid) {
        printf("\033c");
        menu();
        SQLHSTMT hstmt5;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt5);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 5." << std::endl;
        }

        s_p_id = 0;
        s_r_id = 0;
        s_surname = L"NULL";
        s_first_name = L"NULL";
        s_surname_2 = L"NULL";
        s_address_id = 0;
        s_birth_date = 0;
        s_class_id = 0;
        s_adm_year = 0;

        cout << "| 1 | 1 | 'da' | 'da' | 'da' | 1 | 2020 | 1 | 2020 |" << endl;
        cout << "Write parant id: ";
        wcin >> s_p_id;
        cout << "Write rating id: ";
        wcin >> s_r_id;
        cout << "Write surname: ";
        wcin >> s_surname;
        cout << "Write first_name: ";
        wcin >> s_first_name;
        cout << "Write surname_2: ";
        wcin >> s_surname_2;
        cout << "Write address_id: ";
        wcin >> s_address_id;
        cout << "Write birth_date: ";
        wcin >> s_birth_date;
        cout << "Write class_id: ";
        wcin >> s_class_id;
        cout << "Write adm_year: ";
        wcin >> s_adm_year;

        swprintf(addSql, sizeof(addSql) / sizeof(addSql[0]),
            L"SELECT add_schoolboy(%d,%d,'%ls','%ls','%ls',%d,%d,%d, %d, '%ls')",
            s_p_id, s_r_id, s_surname.c_str(), s_first_name.c_str(), s_surname_2.c_str(), s_address_id, s_birth_date, s_class_id, s_adm_year, uid.c_str());

        retcode = SQLExecDirectW(hstmt5, addSql, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 7." << std::endl;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt5);
    }

    void remove(wstring uid) {
        printf("\033c");
        menu();

        SQLHSTMT hstmt7;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt7);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 7." << std::endl;
        }
        s_id = 0;
        cout << "Write Id: ";
        wcin >> s_id;

        swprintf(delSql, sizeof(delSql) / sizeof(delSql[0]),
            L"SELECT del_schoolboy(%d, '%ls')",
            s_id, uid.c_str());

        retcode = SQLExecDirectW(hstmt7, delSql, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 9." << std::endl;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt7);
    }

    void update(wstring uid) {
        printf("\033c");
        menu();

        SQLHSTMT hstmt10;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt10);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 10." << std::endl;
        }

        cout << "| 1 | 1 | 'da' | 'da' | 'da' | 1 | 2020 | 1 | 2020 | " << endl;
        cout << "Write schoolboy id: ";
        wcin >> s_id;
        cout << "Write parant id: ";
        wcin >> s_p_id;
        cout << "Write rating id: ";
        wcin >> s_r_id;
        cout << "Write surname: ";
        wcin >> s_surname;
        cout << "Write first_name: ";
        wcin >> s_first_name;
        cout << "Write surname_2: ";
        wcin >> s_surname_2;
        cout << "Write address_id: ";
        wcin >> s_address_id;
        cout << "Write birth_date: ";
        wcin >> s_birth_date;
        cout << "Write class_id: ";
        wcin >> s_class_id;
        cout << "Write adm_year: ";
        wcin >> s_adm_year;

        swprintf(updateSql, sizeof(updateSql) / sizeof(updateSql[0]),
            L"SELECT update_schoolboy(%d,%d,%d,'%ls','%ls','%ls',%d,%d,%d, %d, '%ls')",
            s_id, s_p_id, s_r_id, s_surname.c_str(), s_first_name.c_str(), s_surname_2.c_str(), s_address_id, s_birth_date, s_class_id, s_adm_year, uid.c_str());

        retcode = SQLExecDirectW(hstmt10, updateSql, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 11." << std::endl;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt10);
    }

    void updateByValue(int id, wstring first, wstring uid) {
        printf("\033c");
        menu();

        SQLHSTMT hstmt10;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt10);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 10." << std::endl;
        }
        s_id = id;
        wstring str;
        int inter;

        if (first == L"s_surname" || first == L"s_first_name" || first == L"s_surname_2") {
            cout << "Write second value: ";
            wcin >> str;
            swprintf(updateSql, sizeof(updateSql) / sizeof(updateSql[0]),
                L"select upd_val_sch_std('%d','%ls','%ls','%ls')",
                s_id, first.c_str(), str.c_str(), uid.c_str());
        }

        if (first == L"s_p_id" || first == L"s_r_id" || first == L"s_address_id" || first == L"s_birth_date" || first == L"s_class_id" || first == L"s_adm_year") {
            cout << "Write second value: ";
            wcin >> inter;
            swprintf(updateSql, sizeof(updateSql) / sizeof(updateSql[0]),
                L"select upd_val_sch_int('%d','%ls',%d,'%ls')",
                s_id, first.c_str(), inter, uid.c_str());
        }

        retcode = SQLExecDirectW(hstmt10, updateSql, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 11." << std::endl;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt10);
    }

    void find() {
        printf("\033c");
        menu();

        SQLHSTMT hstmt_test1;

        cout << "Write text: ";
        wcin >> findText;

        swprintf(searchSql, sizeof(searchSql) / sizeof(searchSql[0]),
            L"SELECT*FROM search_columns('%ls', '{schoolboy}')",
            findText.c_str());

        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt_test1);

        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check." << std::endl;
        }

        retcode = SQLExecDirectW(hstmt_test1, searchSql, SQL_NTS);

        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error executing SQL query." << std::endl;
        }

        cout << "| schema_name |" << " table_name |" << " column_name |" << " row_ctid |" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        while (SQLFetch(hstmt_test1) == SQL_SUCCESS) {
            SQLGetData(hstmt_test1, 1, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L"| %s /", colData);

            SQLGetData(hstmt_test1, 2, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s /", colData);

            SQLGetData(hstmt_test1, 3, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s /", colData);

            SQLGetData(hstmt_test1, 4, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s |\n", colData);
        }

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt_test1);
        int exit;
        cout << endl;
        cout << "Write rand-number";
        cin >> exit;
    }

    void print() {
        printf("\033c");
        menu();

        SQLHSTMT hstmt_test3;
        wcscpy_s(query, 1024, L"SELECT * FROM schoolboy ORDER BY s_id");

        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt_test3);

        if (retcode != SQL_SUCCESS) {
             std::cerr << "Error operation check." << std::endl;
         }

        retcode = SQLExecDirectW(hstmt_test3, query, SQL_NTS);

        if (retcode != SQL_SUCCESS) {
             std::cerr << "Error executing SQL query." << std::endl;
        }

        cout << "| s_id |" << " s_p_id |" << " s_r_id |" << " s_surname |" << " s_first_name |" << " s_surname_2 |" << " s_address |" << " s_birth_date |" << " s_class |" << " s_adm_year |" << endl;
        cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
        while (SQLFetch(hstmt_test3) == SQL_SUCCESS) {
              SQLGetData(hstmt_test3, 1, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
              wprintf(L"| %s /", colData);

              SQLGetData(hstmt_test3, 2, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
              wprintf(L" %s /", colData);

              SQLGetData(hstmt_test3, 3, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
              wprintf(L" %s /", colData);

              SQLGetData(hstmt_test3, 4, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
              wprintf(L" %s /", colData);

              SQLGetData(hstmt_test3, 5, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
              wprintf(L" %s /", colData);

              SQLGetData(hstmt_test3, 6, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
              wprintf(L" %s /", colData);

              SQLGetData(hstmt_test3, 7, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
              wprintf(L" %s /", colData);

              SQLGetData(hstmt_test3, 8, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
              wprintf(L" %s /", colData);

              SQLGetData(hstmt_test3, 9, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
              wprintf(L" %s /", colData);

              SQLGetData(hstmt_test3, 10, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
              wprintf(L" %s |\n", colData);
        }

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt_test3);

        int exit;
        cout << endl;
        cout << "Write rand-number";
        cin >> exit;
    }
};

class Rating : Sctructure {
public:
    using Sctructure::Sctructure;

    int r_id = 0;
    int r_year = 0;
    int r_class_id = 0;
    int r_subject_id = 0;
    int r_point_quarter = 0;
    int r_point_part_year = 0;
    int r_point_year = 0;
    int r_point_exam = 0;
    int r_point_end = 0;

    wstring findText = L"NULL";

    void add(wstring uid) {
        printf("\033c");
        menu();
        SQLHSTMT hstmt5;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt5);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 5." << std::endl;
        }

        r_year = 0;
        r_class_id = 0;
        r_subject_id = 0;
        r_point_quarter = 0;
        r_point_part_year = 0;
        r_point_year = 0;
        r_point_exam = 0;
        r_point_end = 0;

        cout << "| 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |" << endl;
        cout << "Write year: ";
        wcin >> r_year;
        cout << "Write class_id: ";
        wcin >> r_class_id;
        cout << "Write subject_id: ";
        wcin >> r_subject_id;
        cout << "Write point_quarter: ";
        wcin >> r_point_quarter;
        cout << "Write point_part_year: ";
        wcin >> r_point_part_year;
        cout << "Write point_year: ";
        wcin >> r_point_year;
        cout << "Write point_exam: ";
        wcin >> r_point_exam;
        cout << "Write point_end: ";
        cin >> r_point_end;

        swprintf(addSql, sizeof(addSql) / sizeof(addSql[0]),
             L"SELECT add_rating(%d,%d,%d,%d,%d,%d,%d,%d, '%ls')",
             r_year, r_class_id, r_subject_id, r_point_quarter, r_point_part_year, r_point_year, r_point_exam, r_point_end, uid.c_str());

        retcode = SQLExecDirectW(hstmt5, addSql, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 7." << std::endl;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt5);
    }

    void remove(wstring uid) {
        printf("\033c");
        menu();

        SQLHSTMT hstmt7;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt7);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 7." << std::endl;
        }
        r_id = 0;
        cout << "Write Id: ";
        wcin >> r_id;

        swprintf(delSql, sizeof(delSql) / sizeof(delSql[0]),
            L"SELECT del_rating(%d, '%ls')",
            r_id, uid.c_str());

        retcode = SQLExecDirectW(hstmt7, delSql, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 9." << std::endl;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt7);
    }

    void update(wstring uid) {
        printf("\033c");
        menu();

        SQLHSTMT hstmt10;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt10);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 10." << std::endl;
        }

        cout << "| 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | " << endl;
        cout << "Write rating id: ";
        wcin >> r_id;
        cout << "Write year: ";
        wcin >> r_year;
        cout << "Write class_id: ";
        wcin >> r_class_id;
        cout << "Write subject_id: ";
        wcin >> r_subject_id;
        cout << "Write point_quarter: ";
        wcin >> r_point_quarter;
        cout << "Write point_part_year: ";
        wcin >> r_point_part_year;
        cout << "Write point_year: ";
        wcin >> r_point_year;
        cout << "Write point_exam: ";
        wcin >> r_point_exam;
        cout << "Write point_end: ";
        cin >> r_point_end;

        swprintf(updateSql, sizeof(updateSql) / sizeof(updateSql[0]),
            L"SELECT update_rating(%d,%d,%d,%d,%d,%d,%d,%d,%d, '%ls')",
            r_id, r_year, r_class_id, r_subject_id, r_point_quarter, r_point_part_year, r_point_year, r_point_exam, r_point_end, uid.c_str());

        retcode = SQLExecDirectW(hstmt10, updateSql, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 11." << std::endl;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt10);
    }

    void updateByValue(int id, wstring first, wstring uid) {
        printf("\033c");
        menu();

        SQLHSTMT hstmt10;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt10);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 10." << std::endl;
        }
        r_id = id;
        int inter;
            
        wcout << "Write value: ";
            wcin >> inter;
            swprintf(updateSql, sizeof(updateSql) / sizeof(updateSql[0]),
                L"select upd_val_rat_int('%d','%ls',%d,'%ls')",
                r_id, first.c_str(), inter, uid.c_str());

        retcode = SQLExecDirectW(hstmt10, updateSql, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 11." << std::endl;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt10);
    }

    void find() {
        printf("\033c");
        menu();

        SQLHSTMT hstmt_test1;

        cout << "Write text: ";
        wcin >> findText;

        swprintf(searchSql, sizeof(searchSql) / sizeof(searchSql[0]),
            L"SELECT*FROM search_columns('%ls', '{rating}')",
            findText.c_str());

        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt_test1);

        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check." << std::endl;
        }

        retcode = SQLExecDirectW(hstmt_test1, searchSql, SQL_NTS);

        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error executing SQL query." << std::endl;
        }

        cout << "| schema_name |" << " table_name |" << " column_name |" << " row_ctid |" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        while (SQLFetch(hstmt_test1) == SQL_SUCCESS) {
            SQLGetData(hstmt_test1, 1, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L"| %s /", colData);

            SQLGetData(hstmt_test1, 2, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s /", colData);

            SQLGetData(hstmt_test1, 3, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s /", colData);

            SQLGetData(hstmt_test1, 4, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s |\n", colData);
        }

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt_test1);
        int exit;
        cout << endl;
        cout << "Write rand-number";
        cin >> exit;
    }

    void print() {
        printf("\033c");
        menu();

        SQLHSTMT hstmt_test2;
        wcscpy_s(query, 1024, L"SELECT * FROM rating ORDER BY r_id");

        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt_test2);

        if (retcode != SQL_SUCCESS) {
                    std::cerr << "Error operation check." << std::endl;
        }

        retcode = SQLExecDirectW(hstmt_test2, query, SQL_NTS);

        if (retcode != SQL_SUCCESS) {
              std::cerr << "Error executing SQL query." << std::endl;
        }

        cout << "| r_id |" << " r_year |" << " r_class |" << " r_subject |" << " r_point_quarter |" << " r_point_part_year |" << " r_point_year |" << " r_point_exam |" << " r_point_end |" << endl;
        cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;
        while (SQLFetch(hstmt_test2) == SQL_SUCCESS) {
              SQLGetData(hstmt_test2, 1, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
              wprintf(L"| %s /", colData);

              SQLGetData(hstmt_test2, 2, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
              wprintf(L" %s /", colData);

              SQLGetData(hstmt_test2, 3, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
              wprintf(L" %s /", colData);

              SQLGetData(hstmt_test2, 4, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
              wprintf(L" %s /", colData);

              SQLGetData(hstmt_test2, 5, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
              wprintf(L" %s /", colData);

              SQLGetData(hstmt_test2, 6, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
              wprintf(L" %s /", colData);

              SQLGetData(hstmt_test2, 7, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
              wprintf(L" %s /", colData);

              SQLGetData(hstmt_test2, 8, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
              wprintf(L" %s /", colData);

              SQLGetData(hstmt_test2, 9, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
              wprintf(L" %s |\n", colData);
        }

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt_test2);

        int exit;
        cout << endl;
        cout << "Write rand-number";
        cin >> exit;
    }
};

class Address : Sctructure {
public:
    using Sctructure::Sctructure;

    int ad_id = 0;

    wstring ad_name = L"NULL";
    wstring findText = L"NULL";

    void add(wstring uid) {
        printf("\033c");
        menu();
        SQLHSTMT hstmt5;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt5);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 5." << std::endl;
        }

        ad_name = L"NULL";

        cout << "| 'da' |" << endl;
        cout << "Write address name: ";
        wcin >> ad_name;

        swprintf(addSql, sizeof(addSql) / sizeof(addSql[0]),
            L"SELECT add_address('%ls', '%ls')",
            ad_name.c_str(), uid.c_str());

        retcode = SQLExecDirectW(hstmt5, addSql, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 7." << std::endl;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt5);
    }

    void remove(wstring uid) {
        printf("\033c");
        menu();

        SQLHSTMT hstmt7;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt7);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 7." << std::endl;
        }
        ad_id = 0;
        cout << "Write Id: ";
        wcin >> ad_id;

        swprintf(delSql, sizeof(delSql) / sizeof(delSql[0]),
            L"SELECT del_address(%d, '%ls')",
            ad_id, uid.c_str());

        retcode = SQLExecDirectW(hstmt7, delSql, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 9." << std::endl;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt7);
    }

    void update(wstring uid) {
        printf("\033c");
        menu();

        SQLHSTMT hstmt10;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt10);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 10." << std::endl;
        }

        cout << "| 1 | 'n' | " << endl;
        cout << "Write address id: ";
        wcin >> ad_id;
        cout << "Write address name: ";
        wcin >> ad_name;

        swprintf(updateSql, sizeof(updateSql) / sizeof(updateSql[0]),
            L"SELECT update_address(%d,'%ls', '%ls')",
            ad_id, ad_name, uid.c_str());

        retcode = SQLExecDirectW(hstmt10, updateSql, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 11." << std::endl;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt10);
    }

    void find() {
        printf("\033c");
        menu();

        SQLHSTMT hstmt_test1;

        cout << "Write text: ";
        wcin >> findText;

        swprintf(searchSql, sizeof(searchSql) / sizeof(searchSql[0]),
            L"SELECT*FROM search_columns('%ls', '{address}')",
            findText.c_str());

        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt_test1);

        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check." << std::endl;
        }

        retcode = SQLExecDirectW(hstmt_test1, searchSql, SQL_NTS);

        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error executing SQL query." << std::endl;
        }

        cout << "| schema_name |" << " table_name |" << " column_name |" << " row_ctid |" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        while (SQLFetch(hstmt_test1) == SQL_SUCCESS) {
            SQLGetData(hstmt_test1, 1, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L"| %s /", colData);

            SQLGetData(hstmt_test1, 2, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s /", colData);

            SQLGetData(hstmt_test1, 3, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s /", colData);

            SQLGetData(hstmt_test1, 4, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s |\n", colData);
        }

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt_test1);
        int exit;
        cout << endl;
        cout << "Write rand-number";
        cin >> exit;
    }

    void print() {
        printf("\033c");
        menu();

        SQLHSTMT hstmt_test2;
        wcscpy_s(query, 1024, L"SELECT * FROM address ORDER BY ad_id");

        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt_test2);

        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check." << std::endl;
        }

        retcode = SQLExecDirectW(hstmt_test2, query, SQL_NTS);

        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error executing SQL query." << std::endl;
        }

        cout << "| address_id |" << " address_name |" << endl;
        cout << "-----------------------------" << endl;
        while (SQLFetch(hstmt_test2) == SQL_SUCCESS) {
            SQLGetData(hstmt_test2, 1, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L"| %s /", colData);

            SQLGetData(hstmt_test2, 2, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s |\n", colData);
        }

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt_test2);

        int exit;
        cout << endl;
        cout << "Write rand-number";
        cin >> exit;
    }
};

class Class : Sctructure {
public:
    using Sctructure::Sctructure;

    int cl_id = 0;
    int cl_name = 0;

    wstring findText = L"NULL";

    void add(wstring uid) {
        printf("\033c");
        menu();
        SQLHSTMT hstmt5;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt5);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 5." << std::endl;
        }

        cl_name = 0;

        cout << "| 1 |" << endl;
        cout << "Write class name: ";
        wcin >> cl_name;

        swprintf(addSql, sizeof(addSql) / sizeof(addSql[0]),
            L"SELECT add_class(%d, '%ls')",
            cl_name, uid.c_str());

        retcode = SQLExecDirectW(hstmt5, addSql, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 7." << std::endl;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt5);
    }

    void remove(wstring uid) {
        printf("\033c");
        menu();

        SQLHSTMT hstmt7;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt7);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 7." << std::endl;
        }
        cl_id = 0;
        cout << "Write Id: ";
        wcin >> cl_id;

        swprintf(delSql, sizeof(delSql) / sizeof(delSql[0]),
            L"SELECT del_class(%d, '%ls')",
            cl_id, uid.c_str());

        retcode = SQLExecDirectW(hstmt7, delSql, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 9." << std::endl;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt7);
    }

    void update(wstring uid) {
        printf("\033c");
        menu();

        SQLHSTMT hstmt10;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt10);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 10." << std::endl;
        }

        cout << "| 1 | 1 | " << endl;
        cout << "Write class id: ";
        wcin >> cl_id;
        cout << "Write class name: ";
        wcin >> cl_name;

        swprintf(updateSql, sizeof(updateSql) / sizeof(updateSql[0]),
            L"SELECT update_class(%d,%d, '%ls')",
            cl_id, cl_name, uid.c_str());

        retcode = SQLExecDirectW(hstmt10, updateSql, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 11." << std::endl;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt10);
    }

    void find() {
        printf("\033c");
        menu();

        SQLHSTMT hstmt_test1;

        cout << "Write text: ";
        wcin >> findText;

        swprintf(searchSql, sizeof(searchSql) / sizeof(searchSql[0]),
            L"SELECT*FROM search_columns('%ls', '{class_}')",
            findText.c_str());

        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt_test1);

        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check." << std::endl;
        }

        retcode = SQLExecDirectW(hstmt_test1, searchSql, SQL_NTS);

        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error executing SQL query." << std::endl;
        }

        cout << "| schema_name |" << " table_name |" << " column_name |" << " row_ctid |" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        while (SQLFetch(hstmt_test1) == SQL_SUCCESS) {
            SQLGetData(hstmt_test1, 1, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L"| %s /", colData);

            SQLGetData(hstmt_test1, 2, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s /", colData);

            SQLGetData(hstmt_test1, 3, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s /", colData);

            SQLGetData(hstmt_test1, 4, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s |\n", colData);
        }

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt_test1);
        int exit;
        cout << endl;
        cout << "Write rand-number";
        cin >> exit;
    }

    void print() {
        printf("\033c");
        menu();

        SQLHSTMT hstmt_test2;
        wcscpy_s(query, 1024, L"SELECT * FROM class_  ORDER BY cl_id");

        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt_test2);

        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check." << std::endl;
        }

        retcode = SQLExecDirectW(hstmt_test2, query, SQL_NTS);

        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error executing SQL query." << std::endl;
        }

        cout << "| class_id |" << " class_name |" << endl;
        cout << "-----------------------------" << endl;
        while (SQLFetch(hstmt_test2) == SQL_SUCCESS) {
            SQLGetData(hstmt_test2, 1, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L"| %s /", colData);

            SQLGetData(hstmt_test2, 2, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s |\n", colData);
        }

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt_test2);

        int exit;
        cout << endl;
        cout << "Write rand-number";
        cin >> exit;
    }
};

class Subject : Sctructure {
public:
    using Sctructure::Sctructure;

    int su_id = 0;

    wstring su_name = L"NULL";
    wstring findText = L"NULL";

    void add(wstring uid) {
        printf("\033c");
        menu();
        SQLHSTMT hstmt5;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt5);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 5." << std::endl;
        }

        su_name = L"NULL";

        cout << "| 'da' |" << endl;
        cout << "Write subject name: ";
        wcin >> su_name;

        swprintf(addSql, sizeof(addSql) / sizeof(addSql[0]),
            L"SELECT add_subject('%ls', '%ls')",
            su_name.c_str(), uid.c_str());

        retcode = SQLExecDirectW(hstmt5, addSql, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 7." << std::endl;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt5);
    }

    void remove(wstring uid) {
        printf("\033c");
        menu();

        SQLHSTMT hstmt7;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt7);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 7." << std::endl;
        }
        su_id = 0;
        cout << "Write Id: ";
        wcin >> su_id;

        swprintf(delSql, sizeof(delSql) / sizeof(delSql[0]),
            L"SELECT del_subject(%d, '%ls')",
            su_id, uid.c_str());

        retcode = SQLExecDirectW(hstmt7, delSql, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 9." << std::endl;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt7);
    }

    void update(wstring uid) {
        printf("\033c");
        menu();

        SQLHSTMT hstmt10;
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt10);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check 10." << std::endl;
        }

        cout << "| 1 | 'da' | " << endl;
        cout << "Write subject id: ";
        wcin >> su_id;
        cout << "Write subject name: ";
        wcin >> su_name;

        swprintf(updateSql, sizeof(updateSql) / sizeof(updateSql[0]),
            L"SELECT update_subject(%d,'%ls', '%ls')",
            su_id, su_name.c_str(), uid.c_str());

        retcode = SQLExecDirectW(hstmt10, updateSql, SQL_NTS);
        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error SQL check 11." << std::endl;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt10);
    }

    void find() {
        printf("\033c");
        menu();

        SQLHSTMT hstmt_test1;

        cout << "Write text: ";
        wcin >> findText;

        swprintf(searchSql, sizeof(searchSql) / sizeof(searchSql[0]),
            L"SELECT*FROM search_columns('%ls', '{subject}')",
            findText.c_str());

        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt_test1);

        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check." << std::endl;
        }

        retcode = SQLExecDirectW(hstmt_test1, searchSql, SQL_NTS);

        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error executing SQL query." << std::endl;
        }

        cout << "| schema_name |" << " table_name |" << " column_name |" << " row_ctid |" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        while (SQLFetch(hstmt_test1) == SQL_SUCCESS) {
            SQLGetData(hstmt_test1, 1, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L"| %s /", colData);

            SQLGetData(hstmt_test1, 2, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s /", colData);

            SQLGetData(hstmt_test1, 3, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s /", colData);

            SQLGetData(hstmt_test1, 4, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s |\n", colData);
        }

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt_test1);
        int exit;
        cout << endl;
        cout << "Write rand-number";
        cin >> exit;
    }

    void print() {
        printf("\033c");
        menu();

        SQLHSTMT hstmt_test2;
        wcscpy_s(query, 1024, L"SELECT * FROM subject ORDER BY su_id");

        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt_test2);

        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error operation check." << std::endl;
        }

        retcode = SQLExecDirectW(hstmt_test2, query, SQL_NTS);

        if (retcode != SQL_SUCCESS) {
            std::cerr << "Error executing SQL query." << std::endl;
        }

        cout << "| subject_id |" << " subject_name |" << endl;
        cout << "-----------------------------" << endl;
        while (SQLFetch(hstmt_test2) == SQL_SUCCESS) {
            SQLGetData(hstmt_test2, 1, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L"| %s /", colData);

            SQLGetData(hstmt_test2, 2, SQL_C_WCHAR, colData, sizeof(colData), &indicator);
            wprintf(L" %s |\n", colData);
        }

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt_test2);

        int exit;
        cout << endl;
        cout << "Write rand-number";
        cin >> exit;
    }
};