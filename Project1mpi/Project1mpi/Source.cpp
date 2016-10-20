#include <mpi.h>
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);

	int rank, size;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank)
	{
		char buf[] = "Hello!";
		MPI_Send(buf, sizeof(buf), MPI_CHAR, 0, 0, MPI_COMM_WORLD);
	}
	else {
		cout << "Process 0 started" << endl;
		for (int i(1); i<size; ++i)
		{
			MPI_Status s;
			MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &s);
			int count;
			MPI_Get_count(&s, MPI_CHAR, &count);

			char *buf = new char[count];
			MPI_Recv(buf, count, MPI_CHAR,
				MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &s);
			cout << "Message from process " << s.MPI_SOURCE << ": "
				<< buf << endl;
			delete[] buf;
		}
		cout << "Done." << endl;
	}

	MPI_Finalize();
	return 0;
}