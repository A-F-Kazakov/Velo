/**
 * @author   Казаков Андрей 
 * @date     16.07.19.
 */

#include <iostream>

#include <sys/sysinfo.h>
#include <sys/termios.h>
#include <sys/sysctl.h>

int main(int argc, char **argv)
{
	struct sysinfo var;

	sysinfo(&var);

		std::cout << "number of processors: " << get_nprocs_conf()
		<< "\nnumber of available processors: " << get_nprocs()
		<< "\nuptime: " << var.uptime
		<< "\ntotalram: " << var.totalram
		<< "\nfreeram: " << var.freeram
		<< "\nshared ram: " << var.sharedram
		<< "\nbuffermemory: " << var.bufferram
		<< "\ntotalswap: " << var.totalswap
		<< "\n numprocessors: " << var.procs
		<< "\ntotalhigh: " << var.totalhigh
		<< "\nfreehigh: " << var.freehigh
		<< "\nmemunit: " << var.mem_unit
		<< std::endl;
}