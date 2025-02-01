#include "app/services/StudentService.cpp"
#include <drogon/drogon.h>

using namespace std;

int main()
{
    drogon::app().registerHandler("/hello",
                                  [](const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback)
                                  {
                                      StudentService service = (std::make_shared<StudentRepository>());
                                      auto students = service.getStudents();

                                      Json::Value jsonArray;
                                      for (const auto &student : students)
                                      {
                                          jsonArray.append(student->toJson()); // Her kullanıcıyı JSON'a çevir
                                      }
                                      auto resp = drogon::HttpResponse::newHttpJsonResponse(jsonArray);
                                      callback(resp);
                                  });

    drogon::app().addListener("0.0.0.0", 8080).run();
    return 0;
}