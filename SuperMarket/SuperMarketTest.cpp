#define APPROVAL_TESTS_HIDE_DEPRECATED_CODE 1
#include "ApprovalTests.hpp"
#include "catch2/catch.hpp"

#include "model/SupermarketCatalog.h"
#include "FakeCatalog.h"
#include "model/ShoppingCart.h"
#include "model/Teller.h"
#include "model/ReceiptPrinter.h"


using namespace ApprovalTests;

TEST_CASE("SingleProductReceipt", "[Supermarket]")
{
    // ARRANGE
    SupermarketCatalog *catalog = new FakeCatalog();
    Product toothbrush("toothbrush", ProductUnit::Each);
    catalog->addProduct(toothbrush, 0.99);
    Product apples("apples", ProductUnit::Kilo);
    catalog->addProduct(apples, 1.99);
    Product soap("soap", ProductUnit::Each);
    catalog->addProduct(soap, 0.59);
    Product shampoo("shampoo", ProductUnit::Each);
    catalog->addProduct(shampoo, 1.19);

    Teller teller(catalog);
    teller.addSpecialOffer(SpecialOfferType::TenPercentDiscount, toothbrush, 10.0);
    teller.addSpecialOffer(SpecialOfferType::ThreeForTwo, soap, 0.0);
    teller.addSpecialOffer(SpecialOfferType::TwoForAmount, shampoo, 2.0);

    ShoppingCart cart;
    cart.addItem(toothbrush);
    cart.addItemQuantity(apples, 2.5);
    cart.addItem(toothbrush);
    cart.addItemQuantity(soap, 3);
    cart.addItemQuantity(shampoo, 2);

    // ACT
    Receipt receipt = teller.checksOutArticlesFrom(cart);

    // Print Compare/Approve
    ReceiptPrinter printer;
    Approvals::verify(printer.printReceipt(receipt));
}



