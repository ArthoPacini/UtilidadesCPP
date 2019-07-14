#if !defined(TARRAY2_INCLUDED) 
#define TARRAY2_INCLUDED

#if !defined(Assert)
#define Assert( _exp ) ((void)0)
#endif // #if !defined(Assert)

#if defined (__GNUC__) || defined (__clang__)
#define FORCE_INLINE __attribute__((always_inline)) inline
#elif defined (_MSC_VER)
#define FORCE_INLINE __forceinline 
#else
#define FORCE_INLINE inline
#endif

#include <cassert>
#include <algorithm>

template<typename T>
class TArray2
{
   public:

      // Typedefs
      typedef T value_type;
      typedef value_type* iterator;
      typedef const value_type* const_iterator;

      // Constructor
      TArray2(size_t rows=1, size_t cols=1)
      : m_Rows(0),
        m_Cols(0),
        m_OwnsData(true),
        p_Data(0)
      {
         resizeTo(rows,cols);
      }

      // Construct given external data
      TArray2(T* pAry, bool ownsData, size_t rows=1, size_t cols=1)
      : m_Rows(rows),
        m_Cols(cols),
        m_OwnsData(ownsData),
        p_Data(pAry)
      {
         Assert(0 != p_Data);
      }

      // Copy constructor
      TArray2(const TArray2<T>& a)
      {
         resizeTo( a.rows(),a.cols() );
         std::copy( a.begin(), a.end(), p_Data);
         m_OwnsData = true;
      }

      // Assignment operator
      TArray2& operator = (const TArray2<T>& a)
      {
         resizeTo( a.rows(),a.cols() );
         std::copy( a.begin(), a.end(), p_Data);
         m_OwnsData = true;
         return *this;
      }

      // Destructor
      ~TArray2()
      {
         if (m_OwnsData) { delete[] p_Data; }
      }

      // Dimensions retrieval
      FORCE_INLINE size_t rows() const { return m_Rows; }
      FORCE_INLINE size_t cols() const { return m_Cols; }
      FORCE_INLINE size_t size() const { return rows()*cols(); }
      FORCE_INLINE size_t bytes() const { return size()*sizeof(value_type); }
      FORCE_INLINE double kiloBytes() const { return size()*sizeof(value_type)/1024; }
      FORCE_INLINE double megaBytes() const { return size()*sizeof(value_type)/1024/1024; }
      FORCE_INLINE double gigaBytes() const { return size()*sizeof(value_type)/1024/1024/1024; }
      FORCE_INLINE double teraBytes() const { return size()*sizeof(value_type)/1024/1024/1024/1024; }

      // Fill with a value
      void fill(value_type val)
      {
         std::uninitialized_fill_n( p_Data, size(), val );
      }

      // Swap contents with another array
      void swap(TArray2<T>& ary)
      {
         std::swap( m_Rows, ary.m_Rows );
         std::swap( m_Cols, ary.m_Cols );
         std::swap( m_OwnsData, ary.m_OwnsData );
         std::swap( p_Data, ary.p_Data );
      }

      // Resize data bank
      void resizeTo(size_t rows, size_t cols)
      {
         // Not allowed for external data
         Assert( m_OwnsData );

         // Sanity check
         size_t nElements = rows*cols;
         Assert( nElements>0 );
         // If we have existing data
         if ( 0 != p_Data )
         {
            // No change, return
            if ( rows==m_Rows && cols==m_Cols )
            {
               return;
            }
            delete[] p_Data;
            p_Data = 0;
         }
         // Allocate data bank
         p_Data = new value_type[nElements];
         m_Rows = rows;
         m_Cols = cols;
      }

      // STL style iterators
      FORCE_INLINE const_iterator begin() const { return p_Data; }
      FORCE_INLINE const_iterator end() const { return p_Data + size(); }
      FORCE_INLINE iterator begin() { return p_Data; }
      FORCE_INLINE iterator end() { return p_Data + size(); }

      // Array indexing operators
      FORCE_INLINE const T& operator () ( size_t i ) const { return p_Data[ checkedIndex(i) ]; }
      FORCE_INLINE const T& operator () ( size_t i, size_t j ) const { return p_Data[ checkedIndex( i, j ) ]; }
      FORCE_INLINE T& operator () ( size_t i ) { return p_Data[ checkedIndex(i) ]; }
      FORCE_INLINE T& operator () ( size_t i, size_t j ) { return p_Data[ checkedIndex( i, j ) ]; }

      // Get pointers to internal data
      FORCE_INLINE const T* c_data() const { return p_Data; }
      FORCE_INLINE T* c_data() { return p_Data; }

   private:

      size_t checkedIndex(size_t indx) const
      {
         Assert( indx < size() );
         return indx;
      }
      size_t checkedIndex(size_t iRow, size_t jCol) const
      {
         size_t k = m_Cols*iRow + jCol;
         Assert( k < size() );
         return k;
      }

   private:

      size_t m_Rows; 
      size_t m_Cols;
      bool m_OwnsData;
      T* p_Data;

}; // class TArray2

#endif // #if !defined(TARRAY2_INCLUDED)