# frozen_string_literal: true

class CreateUsers < ActiveRecord::Migration[6.0]
  def change
    create_table :users do |t|
      t.string :email
      t.string :username
      t.float :points
      t.timestamp :last_active
      t.boolean :admin
      t.string :password_digest

      t.timestamps
    end
    add_index :users, :email, unique: true
  end
end
