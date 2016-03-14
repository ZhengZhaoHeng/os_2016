#include <cstdio>

void make_table(unsigned int va, unsigned int pa)
{
	unsigned int pde_idx = va >> 22;
	unsigned int PT = pde_idx - 0x300 + 0x1;

	unsigned int pde_ctx = (PT << 12) + 0x3;

	unsigned int pte_idx = (va >> 12) & 0x3ff;

	unsigned int pte_ctx = pa & ~0x3FF | 0x3;

	printf("va 0x%08x, pa 0x%08x\npde_idx 0x%08x, pde_ctx 0x%08x, pte_idx 0x%08x, pte_ctx 0x%08x\n", va, pa, pde_idx, pde_ctx, pte_idx, pte_ctx);
}

unsigned int main()
{
	make_table(0xcd82c07c, 0x0c20907c);
	make_table(0xc2265b1f, 0x0d8f1b1f);
	make_table( 0xcc386bbc,  0x0414cbbc);
	make_table( 0xc7ed4d57,  0x07311d57);
	make_table( 0xca6cecc0,  0x0c9e9cc0);
	make_table( 0xc18072e8,  0x007412e8);
	make_table( 0xcd5f4b3a,  0x06ec9b3a);
	make_table( 0xcc324c99,  0x0008ac99);
	make_table( 0xc7204e52,  0x0b8b6e52);
	make_table( 0xc3a90293,  0x0f1fd293);
	make_table( 0xce6c3f32,  0x007d4f32);
	return 0;
}