#
# Makefile for the linux YAFFS filesystem routines.
#

CFLAGS_yaffs_guts.o = -O0

obj-$(CONFIG_YAFFS_FS) += yaffs.o

yaffs-y := yaffs_ecc.o yaffs_vfs.o yaffs_guts.o yaffs_checkptrw.o
yaffs-y += yaffs_packedtags1.o yaffs_packedtags2.o yaffs_nand.o
yaffs-y += yaffs_tagscompat.o yaffs_tagsmarshall.o
yaffs-y += yaffs_mtdif.o
yaffs-y += yaffs_nameval.o yaffs_attribs.o
yaffs-y += yaffs_allocator.o
yaffs-y += yaffs_yaffs1.o
yaffs-y += yaffs_yaffs2.o
yaffs-y += yaffs_bitmap.o
yaffs-y += yaffs_summary.o
yaffs-y += yaffs_verify.o

