#include "Offer.h"

PercentDiscountOffer::PercentDiscountOffer(const Product& product, double percentDiscount)
    : product(product), percentDiscount(percentDiscount) {}

Discount* PercentDiscountOffer::handleOffer(SupermarketCatalog* catalog, const std::map<Product, double>& productQuantities)
{
    const auto& productQuantity = productQuantities.find(product);
    if (productQuantity == productQuantities.end())
        return nullptr;

    double quantity = productQuantity->second;
    double unitPrice = catalog->getUnitPrice(product);

    return new Discount(std::to_string(percentDiscount) + "% off", -quantity * unitPrice * percentDiscount / 100.0, product);
}


BuyXQtyPayYQtyOffer::BuyXQtyPayYQtyOffer(const Product& product, int x, int y)
    : product(product), x(x), y(y) {}

Discount* BuyXQtyPayYQtyOffer::handleOffer(SupermarketCatalog* catalog, const std::map<Product, double>& productQuantities)
{
    const auto& productQuantity = productQuantities.find(product);
    if (productQuantity == productQuantities.end())
        return nullptr;

    double quantity = productQuantity->second;
    int quantityAsInt = (int)quantity;

    if (quantityAsInt < x)
        return nullptr;

    double unitPrice = catalog->getUnitPrice(product);
    int numberOfXs = quantityAsInt / x;

    double discountAmount = quantity * unitPrice - ((numberOfXs * y * unitPrice) + quantityAsInt % x * unitPrice);
    return new Discount(std::to_string(x) + " for " + std::to_string(y), -discountAmount, product);
}


BuyXQtyPayAmountOffer::BuyXQtyPayAmountOffer(const Product& product, int x, double amount)
    : product(product), x(x), amount(amount) {}

Discount* BuyXQtyPayAmountOffer::handleOffer(SupermarketCatalog* catalog, const std::map<Product, double>& productQuantities)
{
    const auto& productQuantity = productQuantities.find(product);
    if (productQuantity == productQuantities.end())
        return nullptr;

    double quantity = productQuantity->second;
    int quantityAsInt = (int)quantity;

    if (quantityAsInt < x)
        return nullptr;

    double unitPrice = catalog->getUnitPrice(product);
    int numberOfXs = quantityAsInt / x;

    double discountTotal = unitPrice * quantity - (amount * numberOfXs + quantityAsInt % x * unitPrice);
    return new Discount(std::to_string(x) + " for " + std::to_string(amount), -discountTotal, product);
}
