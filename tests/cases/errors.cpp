//
// Created by Arthur Motelevicz on 07/08/24.
//
#include "TestsHelper.h"
#include <cedromd>

TEST_CASE("Errors handling")
{
  cedro::md::CMDBaseManager manager(CEDRO_USERNAME, CEDRO_PASSWORD, CEDRO_SOFTKEY);

  std::promise<bool> sendPromise;
  std::future<bool> sendFuture = sendPromise.get_future();

  std::shared_ptr<bb::network::rs::Stream> streamPtr;

  auto messenger = std::make_shared<bb::RawMessenger>();

  manager.connect([&](bool success, const std::shared_ptr<bb::network::rs::Stream>& stream)
  {
    streamPtr = stream;
    sendPromise.set_value(success);
  });

  TestHelper::waitForSuccess(sendFuture, streamPtr, 5);

  auto testError = [&](cedro::md::Error::Type expectedError, const std::string& command, const std::string& testName)
  {
    std::promise<bool> errorPromise;
    std::future<bool> errorFuture = errorPromise.get_future();

    manager.setErrorCallback([&](const cedro::md::Error& error, const std::string& msg)
    {
       REQUIRE((error == expectedError));
      logI << ("Error: " + error.toString() + " Msg: " + msg);
       errorPromise.set_value(true);
    });

    messenger->sendMessage(streamPtr, command, nullptr);
    TestHelper::waitForSuccess(errorFuture, streamPtr, 5);
  };

  SECTION("Error 1: INVALID_COMMAND")
  {
    testError(cedro::md::Error::INVALID_COMMAND, "INVALID_CMD PARAM\n", "Invalid Command Test");
  }

  SECTION("Error 2: OBJECT_NOT_FOUND")
  {
    testError(cedro::md::Error::OBJECT_NOT_FOUND, "SQT AAAAA\n", "Object Not Found Test");
  }

  SECTION("Error 3: NO_PERMISSION")
  {
    testError(cedro::md::Error::NO_PERMISSION, "SQT PETR4\n", "No Permission Test");
  }

  SECTION("Error 4: MISSING_PARAMETER")
  {
    testError(cedro::md::Error::MISSING_PARAMETER, "GQT WDOU24\n", "Missing Parameter Test");
  }

  SECTION("Error 5: NO_PARAMETERS")
  {
    testError(cedro::md::Error::NO_PARAMETERS, "INVALID_CMD\n", "No Parameters Test");
  }

  SECTION("Error 6: DOUBLE_CONNECTION")
  {
    std::promise<bool> errorPromise;
    std::future<bool> errorFuture = errorPromise.get_future();

    manager.setErrorCallback([&](const cedro::md::Error& error, const std::string& msg)
    {
      REQUIRE(error == cedro::md::Error::DOUBLE_CONNECTION);
      logI << ("Error: " + error.toString() + " Msg: " + msg);
      errorPromise.set_value(true);
    });

    cedro::md::CMDBaseManager manager2(CEDRO_USERNAME, CEDRO_PASSWORD, CEDRO_SOFTKEY);
    manager2.connect([&](bool success, const std::shared_ptr<bb::network::rs::Stream>& stream){});

    TestHelper::waitForSuccess(errorFuture, streamPtr, 60);
  }
}
