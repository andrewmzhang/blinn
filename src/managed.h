
#ifndef __managed_h__
#define __managed_h__

class managed {
	public:

		void *operator new(size_t len) {
			void *ptr;
			cudaMallocManaged(&ptr, len);
			cudaDeviceSynchronize();
			return ptr;
		}

		void operator delete(void *ptr) {
			cudaDeviceSynchronize();
			cudaFree(ptr);
		}
};

#endif
