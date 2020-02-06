# frozen_string_literal: true

namespace :bce do
  desc 'Make an user admin'
  task :grant_admin, [:email] => [:environment] do |_task, args|
    user = User.find_by email: args.email

    raise "no user with email: #{args.email}" unless user

    user.admin = true
    user.save
  end

  desc 'Revoke admin status'
  task :revoke_admin, [:email] => [:environment] do |_task, args|
    user = User.find_by email: args.email

    raise "no user with email: #{args.email}" unless user

    user.admin = false
    user.save
  end
end
