#include <ast/record-type.hh>

using namespace ucc;
using namespace ast;

RecordType::RecordType(const ucc::parse::location& loc,
                       RecordDecl::RecordType type,
                       const ucc::misc::Symbol& name)
    : Type(loc)
    , name_(name)
    , type_(type)
    , def_(nullptr)
{}

RecordType::~RecordType()
{}

const ucc::misc::Symbol& RecordType::name_get() const
{
    return name_;
}

ucc::misc::Symbol& RecordType::name_get()
{
    return name_;
}

RecordDecl::RecordType RecordType::type_get() const
{
    return type_;
}

const RecordDecl* RecordType::def_get() const
{
    return def_;
}

RecordDecl* RecordType::def_get()
{
    return def_;
}

void RecordType::def_set(RecordDecl* decl)
{
    def_ = decl;
}

void RecordType::accept(Visitor& v)
{
    v(*this);
}

void RecordType::accept(ConstVisitor& v) const
{
    v(*this);
}
