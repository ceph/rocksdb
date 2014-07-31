AUTOMAKE_OPTIONS = subdir-objects
OPT ?= -DNDEBUG

ACLOCAL_AMFLAGS = -I m4
WARNING_FLAGS = -Wall -Werror 
ROCKSDB_CFLAGS = -g -O2 -fPIC
ROCKSDB_CXXFLAGS = -std=c++11 -g -O2 -fPIC
GFLAG = gflags
noinst_LTLIBRARIES = librocksdb.la

librocksdb_la_CFLAGS = $(WARNING_FLAGS) $(ROCKSDB_CFLAGS) -I$(srcdir) -I$(srcdir)/include -DOS_LINUX -DROCKSDB_PLATFORM_POSIX -fno-builtin-memcmp $(OPT) -DHAVE_JEMALLOC -Woverloaded-virtual
librocksdb_la_CXXFLAGS = $(WARNING_FLAGS) $(ROCKSDB_CXXFLAGS) -I$(srcdir) -I$(srcdir)/include -DOS_LINUX -DROCKSDB_PLATFORM_POSIX -fno-builtin-memcmp $(OPT) -DHAVE_JEMALLOC -Woverloaded-virtual -DROCKSDB_ATOMIC_PRESENT -DROCKSDB_FALLOCATE_PRESENT 
librocksdb_la_LDFLAGS = -shared -Wl,-soname -Wl
if WITH_ATOMIC
   librocksdb_la_CFLAGS += -DROCKSDB_ATOMIC_PRESENT
   librocksdb_la_CXXFLAGS += -DROCKSDB_ATOMIC_PRESENT
endif

if WITH_FALLOCATE
   librocksdb_la_CFLAGS += -DROCKSDB_FALLOCATE_PRESENT
   librocksdb_la_CXXFLAGS += -DROCKSDB_FALLOCATE_PRESENT
endif
#
librocksdb_la_LDFLAGS += -lpthread 
if WITH_TCMALLOC
   librocksdb_la_LDFLAGS += -ltcmalloc
if WITH_RT
   librocksdb_la_LDFLAGS += -lrt
endif
endif
if WITH_SNAPPY
   librocksdb_la_CFLAGS += -DSNAPPY
   librocksdb_la_CXXFLAGS += -DSNAPPY
   librocksdb_la_LDFLAGS += -lsnappy
endif
if WITH_Z
   librocksdb_la_CFLAGS += -DZLIB
   librocksdb_la_CXXFLAGS += -DZLIB
   librocksdb_la_LDFLAGS += -lz
endif
if WITH_BZ2
   librocksdb_la_CFLAGS += -DBZIP2
   librocksdb_la_CXXFLAGS += -DBZIP2
   librocksdb_la_LDFLAGS += -lbz2
endif
if WITH_GOOGLE_FLAGS
   GFLAGS = google
   librocksdb_la_CFLAGS += -DGFLAGS
   librocksdb_la_CXXFLAGS += -DGFLAGS
   librocksdb_la_LDFLAGS += -lgflags
endif
if WITH_GFLAGS_FLAGS
   GFLAGS = gflags
   librocksdb_la_CFLAGS += -DGFLAGS
   librocksdb_la_CXXFLAGS += -DGFLAGS
   librocksdb_la_LDFLAGS += -lgflags
endif

SOURCE_FILES = db/builder.cc \
	db/c.cc \
	db/column_family.cc \
	db/compaction.cc \
	db/compaction_picker.cc \
	db/db_filesnapshot.cc \
	db/dbformat.cc \
	db/db_impl.cc \
	db/db_impl_debug.cc \
	db/db_impl_readonly.cc \
	db/db_iter.cc \
	db/db_stats_logger.cc \
	db/file_indexer.cc \
	db/filename.cc \
	db/internal_stats.cc \
	db/log_reader.cc \
	db/log_writer.cc \
	db/memtable.cc \
	db/memtable_list.cc \
	db/merge_helper.cc \
	db/merge_operator.cc \
	db/repair.cc \
	db/table_cache.cc \
	db/table_properties_collector.cc \
	db/tailing_iter.cc \
	db/transaction_log_impl.cc \
	db/version_edit.cc \
	db/version_set.cc \
	db/write_batch.cc \
	table/block_based_table_builder.cc \
	table/block_based_table_factory.cc \
	table/block_based_table_reader.cc \
	table/block_builder.cc \
	table/block.cc \
	table/block_hash_index.cc \
	table/filter_block.cc \
	table/flush_block_policy.cc \
	table/format.cc \
	table/iterator.cc \
	table/merger.cc \
	table/meta_blocks.cc \
	table/plain_table_builder.cc \
	table/plain_table_factory.cc \
	table/plain_table_reader.cc \
	table/table_properties.cc \
	table/two_level_iterator.cc \
	util/arena.cc \
	util/auto_roll_logger.cc \
	util/blob_store.cc \
	util/bloom.cc \
	util/build_version.cc \
	util/cache.cc \
	util/coding.cc \
	util/comparator.cc \
	util/crc32c.cc \
	util/dynamic_bloom.cc \
	util/env.cc \
	util/env_hdfs.cc \
	util/env_posix.cc \
	util/filter_policy.cc \
	util/hash.cc \
	util/hash_cuckoo_rep.cc \
	util/hash_linklist_rep.cc \
	util/hash_skiplist_rep.cc \
	util/histogram.cc \
	utilities/backupable/backupable_db.cc \
	utilities/geodb/geodb_impl.cc \
	utilities/merge_operators/put.cc \
	utilities/merge_operators/string_append/stringappend2.cc \
	utilities/merge_operators/string_append/stringappend.cc \
	utilities/merge_operators/uint64add.cc \
	utilities/redis/redis_lists.cc \
	utilities/ttl/db_ttl_impl.cc \
	util/ldb_cmd.cc \
	util/ldb_tool.cc \
	util/log_buffer.cc \
	util/logging.cc \
	util/murmurhash.cc \
	util/options.cc \
	util/perf_context.cc \
	util/skiplistrep.cc \
	util/slice.cc \
	util/statistics.cc \
	util/status.cc \
	util/string_util.cc \
	util/sync_point.cc \
	util/thread_local.cc \
	util/vectorrep.cc \
	util/xxhash.cc \
	port/port_posix.cc \
	port/stack_trace.cc 


SOURCE_H = util/ldb_cmd_execute_result.h \
	util/xxhash.h \
	util/mutexlock.h \
	util/logging.h \
	util/coding.h \
	util/posix_logger.h \
	util/crc32c.h \
	util/ldb_cmd.h \
	util/hash_linklist_rep.h \
	util/log_buffer.h \
	util/sync_point.h \
	util/murmurhash.h \
	util/autovector.h \
	util/perf_context_imp.h \
	util/testharness.h \
	util/hash.h \
	util/histogram.h \
	util/stats_logger.h \
	util/arena.h \
	util/string_util.h \
	util/stl_wrappers.h \
	util/stop_watch.h \
	util/statistics.h \
	util/build_version.h \
	util/benchharness.h \
	util/auto_roll_logger.h \
	util/dynamic_bloom.h \
	util/random.h \
	util/hash_skiplist_rep.h \
	util/testutil.h \
	util/thread_local.h \
	util/blob_store.h \
	util/hash_cuckoo_rep.h \
	db/compaction_picker.h \
	db/internal_stats.h \
	db/builder.h \
	db/memtable.h \
	db/write_batch_internal.h \
	db/file_indexer.h \
	db/log_format.h \
	db/merge_context.h \
	db/log_writer.h \
	db/snapshot.h \
	db/table_properties_collector.h \
	db/log_reader.h \
	db/version_set.h \
	db/merge_helper.h \
	db/table_cache.h \
	db/version_edit.h \
	db/memtable_list.h \
	db/db_impl_readonly.h \
	db/tailing_iter.h \
	db/filename.h \
	db/db_iter.h \
	db/compaction.h \
	db/column_family.h \
	db/skiplist.h \
	db/transaction_log_impl.h \
	db/dbformat.h \
	db/db_impl.h \
	table/block.h \
	table/iter_heap.h \
	table/block_based_table_reader.h \
	table/iterator_wrapper.h \
	table/block_builder.h \
	table/table_builder.h \
	table/plain_table_factory.h \
	table/block_hash_index.h \
	table/plain_table_reader.h \
	table/table_reader.h \
	table/meta_blocks.h \
	table/format.h \
	table/block_based_table_builder.h \
	table/merger.h \
	table/plain_table_builder.h \
	table/two_level_iterator.h \
	table/block_based_table_factory.h \
	table/filter_block.h \
	utilities/geodb/geodb_impl.h \
	utilities/merge_operators.h \
	utilities/merge_operators/string_append/stringappend2.h \
	utilities/merge_operators/string_append/stringappend.h \
	utilities/ttl/db_ttl_impl.h \
	utilities/redis/redis_list_iterator.h \
	utilities/redis/redis_lists.h \
	utilities/redis/redis_list_exception.h \
	include/utilities/geo_db.h \
	include/utilities/stackable_db.h \
	include/utilities/db_ttl.h \
	include/utilities/utility_db.h \
	include/utilities/backupable_db.h \
	include/rocksdb/universal_compaction.h \
	include/rocksdb/options.h \
	include/rocksdb/comparator.h \
	include/rocksdb/flush_block_policy.h \
	include/rocksdb/ldb_tool.h \
	include/rocksdb/perf_context.h \
	include/rocksdb/slice_transform.h \
	include/rocksdb/filter_policy.h \
	include/rocksdb/types.h \
	include/rocksdb/write_batch.h \
	include/rocksdb/statistics.h \
	include/rocksdb/slice.h \
	include/rocksdb/merge_operator.h \
	include/rocksdb/iterator.h \
	include/rocksdb/env.h \
	include/rocksdb/compaction_filter.h \
	include/rocksdb/table_properties.h \
	include/rocksdb/db.h \
	include/rocksdb/table.h \
	include/rocksdb/status.h \
	include/rocksdb/memtablerep.h \
	include/rocksdb/version.h \
	include/rocksdb/c.h \
	include/rocksdb/transaction_log.h \
	include/rocksdb/cache.h 

noinst_HEADERS = $(SOURCE_H)

librocksdb_la_SOURCES = $(SOURCE_FILES)
