/*
 * File:   main.cpp
 * Author: Jeff
 *
 * Created on November 24, 2014, 11:59 AM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstddef>
#include <ctime>
#include <time.h>
using namespace std;

int max_size = 1;
int z = 0;
int Com_string (string x[], string y[], int m, int n, string *res, int &max)
{
    int **seq = new int *[m + 1];
    for (int i = 0; i < m + 1; i++)
        seq[i] = new int[n + 1];
    int min = 0;
    if (n < m)
        min = n;
    else
        min = m;
    int *com_seq = new int[min*2];
    int *com_seq_y = new int[min*2];

    int k = 0;
    max = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (x[i] == y[j])
            {
                if (i == 0 || j == 0)
                {
                    seq[i + 1][j + 1] = 1;
                    if (max == 0)
                    {
                        max = seq[i + 1][j + 1];
                    }
                }
                else
                {
                    seq[i + 1][j + 1] = seq[i][j] + 1;
                    if (seq[i + 1][j + 1] > max)
                    {
                        max = seq[i + 1][j + 1];
                    }
                }
                com_seq[k] = i;
                com_seq_y[k] = j;
                k++;
            }
            else
            {
                seq[i + 1][j + 1] = 0;
            }
        }
    }
    int h = 0;
    int cont = 0;
    int repeat = 0;
    for (int i = 0; i < k; i++)
    {
        if (com_seq[i] != com_seq[i + 1] || (i == k - 1))
        {
            res[h] = x[com_seq[i]];
            if (i != k - 1)
            {

              /*  if (seq[com_seq[i] + 2][com_seq_y[i] + 2] < seq[com_seq[i] + 1][com_seq_y[i] + 1])
                {
                    h++;
                  //  res[h] = "zzzzzz*****";
                    z++;
                }*/
            }

            h++;
        }
        else
        {
            if (com_seq_y[i] - com_seq_y[i - 1] == 1)
            {

                res[h] = x[com_seq[i]];
                if ((com_seq[i] + 2 < m + 1) && (com_seq_y[i] + 2 < n + 1))
                {
                  /*  if (seq[com_seq[i] + 2][com_seq_y[i] + 2] < seq[com_seq[i] + 1][com_seq_y[i] + 1])
                    {
                        h++;
                        res[h] = "zzzzzz*****";
                        z++;
                    }*/
                }
                h++;
                i++;
            }
        }

    }
   
    for (int i = 0; i < m + 1; i++)
    {
        delete [] seq[i];
    }
    delete [] seq;
    delete [] com_seq;
    delete [] com_seq_y;
    return h;
}


int LCS_DP (string x[], string y[], int m, int n , int max_in, string *res, int status)
{
    int **lcs = new int *[m + 1];
    for (int i = 0; i < m + 1; i++)
    {
        lcs[i] = new int[n + 1];
    }
    int max = 0;
    int max_index_i = 0;
    // int max_index_j = 0;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {

            if (x[i] == y[j])
            {
                if (i == 0 || j == 0)
                {
                    lcs[i + 1][j + 1] = 1;
                    if (max == 0)
                    {
                        max = lcs[i + 1][j + 1];
                        max_index_i = i;
                        //    max_index_j = j;
                    }
                }
                else
                {   
                    lcs[i + 1][j + 1] = lcs[i][j] + 1;
                   
                    if (lcs[i + 1][j + 1] > max)
                    {
                        max = lcs[i + 1][j + 1];
                        max_index_i = i;
                    }
                     if (max == max_in && status != 1)
                    {
                        int cnt = max_in;
                        int index_i = i;
                        while (cnt != 0)
                        {
                            cnt--;
                            if (res[cnt] != x[index_i])
                            {
                                for (int i = 0; i < m + 1; i++)
                                {
                                    delete [] lcs[i];
                                }
                                delete [] lcs;
                                return 2;
                            } // must be something with smaller size, need to modify the com string
                            index_i--;
                            for (int i = 0; i < m + 1; i++)
                            {
                                delete [] lcs[i];
                            }
                            delete [] lcs;
                            return 1;
                        }
                    }
                }
            }
            else
            {
                lcs[i + 1][j + 1] = 0;
            }
        }
    }
    if (max_in == max)  // the size is the same
    {
        int cnt = max;
        while (cnt != 0)
        {
            cnt--;
            if (status == 1)
                res[cnt] = x[max_index_i];
            if (res[cnt] != x[max_index_i])
            {
                for (int i = 0; i < m + 1; i++)
                {
                    delete [] lcs[i];
                }
                delete [] lcs;
                return 2;
            } // must be something smaller size, need to modify the com string
            max_index_i--;
        }
    }
    else if (max_in < max) // shouldn't happen. if occurs, means unluck man
    {
        for (int i = 0; i < m + 1; i++)
        {
            delete [] lcs[i];
        }
        delete [] lcs;
        return 3;
    }
    else    //< means
    {
        for (int i = 0; i < m + 1; i++)
        {
            delete [] lcs[i];
        }
        delete [] lcs;
        return 2;
    }

    for (int i = 0; i < m + 1; i++)
    {
        delete [] lcs[i];
    }
    delete [] lcs;

   /*  for (int i = 0; i < max; i++)
        {
            cout << res[i];
            if (i != max - 1)
                cout << " ";
        }
    cout <<"\n";*/
    return 1;
}


int main(int argc, char **argv)
{
 //   clock_t t;
  //  t = clock();
    string line;
    ifstream myfile (argv[1]);
    string *line_cur;
    string *line_prev;
    string *all_comm_strings;
    string *lcd;
    int curr = 0;
    int prev = 0;
    int line_count = 0;
    int comm_size = 0;
    int max = -1;
    int l = 2;
    int l_1 = 2;
    int max_line = 0;
    int tmp = 0;
    if (myfile.is_open())
    {

        while ( getline (myfile, line) ) // begin to parse the line
        {
            istringstream ss(line);
            int i = 0;
            int tmp_size = line.size() + 1;
            if (line_count == 0 || (max_line / (double)tmp_size < 0.6))
            {
                
                max_line = tmp_size;
                max_size = tmp_size;
                if (line_count != 0)
                    delete []line_cur;
                line_cur = new string[max_size / 2];
                while (!(ss.eof()))
                {
                    ss >> line_cur[i];
                    i++;
                }
            }
            else
            {
                while (!(ss.eof()))
                {
                    ss >> line_cur[i];
                    i++;
                }
            }
            if (line_count == 0)
            {
                all_comm_strings = new string[i + 1];
                line_prev = new string[i + 1];
                for (int j = 0; j < i; j++)
                {
                    line_prev[j] = line_cur[j];
                }
                prev = i;
                tmp = i;
            }


            curr = i;
            if (line_count == 1)
            {    
                comm_size = Com_string(line_cur, line_prev, curr, prev, all_comm_strings, max) ;
                lcd = new string[comm_size];
                //LCS_DP(all_comm_strings,line_cur,comm_size,curr,max,lcd,1);
            }
            else if (line_count == l && (z > 0|| l == 2) )
            {
                comm_size = Com_string(all_comm_strings, line_cur, comm_size, curr, all_comm_strings, max) ;
                LCS_DP(all_comm_strings, line_cur, comm_size, curr, max, lcd, 1);
                
                l =l*2;
            }
            else if (line_count != 0)
            {   
                int temp;
                if (line_count != 2)
                    temp = LCS_DP(all_comm_strings, line_cur, comm_size, curr, max, lcd, 0);
                else
                    temp = LCS_DP(all_comm_strings, line_cur, comm_size, curr, max, lcd, 1);
                if (temp == 2)
                {
                    comm_size = Com_string(all_comm_strings, line_cur, comm_size, curr, all_comm_strings, max) ;
                    LCS_DP(all_comm_strings, line_cur, comm_size, curr, max, lcd, 1);
                }
            }
            line_count++;
            if (line_count == 2)
                delete [] line_prev;
            if(line_count == l&&z<1){
                l=l*2;
            }
        }
    }
    if (line_count == 1)
    {
        for (int i = 0; i < tmp; i++)
        {
            cout << line_cur[i];
            if (i != tmp - 1)
                cout << " ";
        }
    }
    else
    {
        if (line_count == 2)
        {
            LCS_DP(all_comm_strings, line_cur, comm_size, curr, max, lcd, 1);
        }
        for (int i = 0; i < max; i++)
        {
            cout << lcd[i];
            if (i != max - 1)
                cout << " ";
        }
    }
    cout << "\n";

    delete [] line_cur;
    delete [] all_comm_strings;
    delete [] lcd;
    return 0;
}

