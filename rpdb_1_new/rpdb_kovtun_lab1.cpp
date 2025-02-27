#include "rpbd.h"

int main() {
    setlocale(LC_ALL, "Russian");
    std::wstring uid, pwd, dsn;
    do
    {
        std::cout << "DSN: ";
        std::wcin >> dsn;
        std::cout << "UID: ";
        std::wcin >> uid;
        std::cout << "PWD: ";
        std::wcin >> pwd;
    } while (pwd == L" ");

    Sctructure S(uid, pwd, dsn), M;   
    S.init(uid);
    Parants P(uid, pwd, dsn);
    Rating R(uid, pwd, dsn);
    Schoolboy Sc(uid, pwd, dsn);
    Address A(uid, pwd, dsn);
    Class C(uid, pwd, dsn);
    Subject Su(uid, pwd, dsn);
    string add, update, remove, search, print, updateByVal;
    wstring updateVal;
    int s = 1;

    printf("\033c");
    M.menu();
    cout << endl;

    while (s != 0)
    {
        printf("\033c");
        M.menu();
        cout << "Write menu-number: ";
        cin >> s;
        switch (s)
        {
        case 1:
            printf("\033c");
            M.menu();
            cout << "Write table name: ";
            cin >> add;
            if (add == "parants") {
                P.add(uid);
            }
            else if(add == "rating") {
                R.add(uid);
            }
            else if (add == "schoolboy") {
                Sc.add(uid);
            }
            else if (add == "address") {
                A.add(uid);
            }
            else if (add == "class") {
                C.add(uid);
            } 
            else if (add == "subject") {
                Su.add(uid);
            }
            break;

        case 2:
            printf("\033c");
            M.menu();
            cout << "Write table name: ";
            cin >> remove;
            if (remove == "parants") {
                P.remove(uid);
            }
            else if (remove == "rating") {
                R.remove(uid);
            }
            else if (remove == "schoolboy") {
                Sc.remove(uid);
            }
            else if (remove == "address") {
                A.remove(uid);
            }
            else if (remove == "class") {
                C.remove(uid);
            }
            else if (remove == "subject") {
                Su.remove(uid);
            }
            break;

        case 3:
            printf("\033c");
            M.menu();
            cout << "Write table name: ";
            cin >> update;
            if (update == "parants") {
                P.update(uid);
            }
            else if (update == "rating") {
                R.update(uid);
            }
            else if (update == "schoolboy") {
                Sc.update(uid);
            }
            else if (update == "address") {
                A.update(uid);
            }
            else if (update == "class") {
                C.update(uid);
            }
            else if (update == "subject") {
                Su.update(uid);
            }
            break;

        case 4:
            printf("\033c");
            M.menu();
            cout << "Write table name: ";
            cin >> search;
            if (search == "parants") {
                P.find();
            }
            else if (search == "rating") {
                R.find();
            }
            else if (search == "schoolboy") {
                Sc.find();
            }
            else if (search == "address") {
                A.find();
            }
            else if (search == "class") {
                C.find();
            }
            else if (search == "subject") {
                Su.find();
            }
            break;

        case 5:
            printf("\033c");
            M.menu();
            cout << "Write table name: ";
            cin >> print;
            if (print == "parants") {
                P.print();
            }
            else if (print == "rating") {
                R.print();
            }
            else if (print == "schoolboy") {
                Sc.print();
            }
            else if (print == "address") {
                A.print();
            }
            else if (print == "class") {
                C.print();
            }
            else if (print == "subject") {
                Su.print();
            }
            else if (print == "history" && uid == L"postgres") {
                S.print();
            }
            break;
        
        case 6:
            printf("\033c");
            M.menu();
            S.all_find();

            break;

        case 7:
            printf("\033c");
            M.menu();
            int id;

            cout << "Write table name: ";
            cin >> updateByVal;
            cout << "Write id: ";
            wcin >> id;
            cout << "Write column: ";
            wcin >> updateVal;

            if (updateByVal == "parants") {
                P.updateByValue(id, updateVal, uid);
            }
            else if (updateByVal == "rating") {
                R.updateByValue(id, updateVal, uid);
            }
            else if (updateByVal == "schoolboy") {
                Sc.updateByValue(id, updateVal, uid);
            }
            else if (updateByVal == "address") {
                //A.updateByValue(id, updateVal, uid);
            }
            else if (updateByVal == "class") {
                //C.updateByValue(id, updateVal, uid);;
            }
            else if (updateByVal == "subject") {
                //Su.updateByValue(id, updateVal, uid);
            }
            break;

        case 8:
            printf("\033c");
            M.menu();
            cout << "Write table name: ";
            cin >> print;
            if (uid == L"postgres") {
                S.structure();
            }
            else {
                break;
            }
            break;

        case 0:
            printf("\033c");
            cout << "                                ................................................" << endl;
            cout << "                                .                                              ." << endl;
            cout << "                                .                Close console                 ." << endl;
            cout << "                                .                                              ." << endl;
            cout << "                                ................................................" << endl;

            break;

        default:
            printf("\033c");
            M.menu();
            cout << "Error, write 0-8..." << endl;
            cout << endl;

            break;
        }
    }
    S.exit(uid);
    return 0;
}

