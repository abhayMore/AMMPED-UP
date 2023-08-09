#pragma once

#include <cstdint>
#include <string>
#include <iostream>
#include "../Header Files/Config.h"
#include "MongoInstanceManager.h"

#include "bsoncxx/builder/stream/document.hpp"
#include "bsoncxx/json.hpp"
#include "bsoncxx/oid.hpp"
#include "mongocxx/client.hpp"
#include "mongocxx/database.hpp"
#include "mongocxx/uri.hpp"
#include <mongocxx/exception/operation_exception.hpp>

namespace learning {
	const mongocxx::uri mongoURI(mongodb_uri);
	const std::string dbName = databaseName;
	const std::string collName = colectionName;
	class MongoDB {
	public:
		MongoDB();
		void connect();
		void insertDocument(const bsoncxx::document::value document);		
		std::tuple<std::string, std::string, std::string> findDocument(const std::string& value);
		bool isDataPresent(const std::string& key, const std::string& value);
		int findScore(const std::string& value);
		void updateDocument(const std::string& key, const int& value, const std::string& newKey, const int& newValue);
		std::vector<std::pair<std::string, int>> getTopScores(int limit);				
		bool getConnection();

	private:
		MongoInstance* instance;

		mongocxx::options::client client_options;
		mongocxx::options::server_api api;
		mongocxx::client conn;
		mongocxx::v_noabi::database ammpedUPDB;
		mongocxx::v_noabi::collection loginInfoCollection;
		std::optional<bsoncxx::document::value> find_one_filtered_result;
	};
}