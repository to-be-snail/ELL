////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  [projectName]
//  File:     ParsingIterator.tcc (dataset)
//  Authors:  Ofer Dekel
//
//  [copyright]
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "SupervisedExampleBuilder.h"
#include "DenseDataVector.h"

namespace dataset
{
    template<typename RowIteratorType, typename VectorEntryParserType>
    ParsingIterator<RowIteratorType, VectorEntryParserType>::ParsingIterator(RowIteratorType&& row_iter, const VectorEntryParserType& parser) :
        _rowIterator(std::move(row_iter)), _instanceParser(parser)
    {
    }

    template<typename RowIteratorType, typename VectorEntryParserType>
    bool ParsingIterator<RowIteratorType, VectorEntryParserType>::IsValid() const
    {
        return _rowIterator.IsValid();
    }

    template<typename RowIteratorType, typename VectorEntryParserType>
    void ParsingIterator<RowIteratorType, VectorEntryParserType>::Next()
    {
        _rowIterator.Next();
    }

    template<typename RowIteratorType, typename VectorEntryParserType>
    SupervisedExample ParsingIterator<RowIteratorType, VectorEntryParserType>::Get() const
    {
        SupervisedExampleBuilder<VectorEntryParserType, FloatDataVector> exampleBuilder(_instanceParser);
        return exampleBuilder.Build(_rowIterator.Get());
    }

    template<typename RowIteratorType, typename VectorEntryParserType>
    std::unique_ptr<IParsingIterator> GetParsingIterator(RowIteratorType&& row_iter, const VectorEntryParserType& parser)
    {
        return std::make_unique<ParsingIterator<RowIteratorType, VectorEntryParserType>>(std::move(row_iter), parser);
    }

}
